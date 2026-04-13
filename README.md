_This project has been created as part of the 42 curriculum by sancuta._

# pipex

## Description

pipex is a program written in C that replicates the behaviour of the shell pipe
operator and basic redirections. It takes an input file, processes its contents
through a series of shell commands, and outputs the result to an output file.

The project goes beyond the mandatory requirements by natively supporting
**multiple pipes** and **here_doc**, managing multiple child processes, and file
descriptors.

---

## Table of Contents

- [Description](#description)
- [Instructions](#instructions)
  - [Compilation](#compilation)
  - [Usage](#usage)
- [Known Limitations](#known-limitations)
- [Algorithm and Data Structure](#algorithm-and-data-structure)
  - [Architecture Overview](#architecture-overview)
  - [Core Data Structure](#core-data-structure)
  - [Memory Management — Arena Allocator](#memory-management--arena-allocator)
  - [Parsing](#parsing)
  - [Execution and Piping](#execution-and-piping)
    - [Child Setup](#child-setup)
    - [Command Resolution](#command-resolution)
    - [Exit Codes](#exit-codes)
  - [here_doc](#here_doc)
  - [Error Handling and Cleanup](#error-handling-and-cleanup)
- [Resources](#resources)
  - [Documentation and References](#documentation-and-references)
  - [AI Usage](#ai-usage)

---

## Instructions

### Compilation

- `make` or `make all` — compiles `pipex`;
- `make clean` — removes object and dependency files;
- `make fclean` — additionally removes the binary and libs;
- `make re` — recompiles the entire project from scratch;
- `make debug` — compiles with the `-g` flag for debugging;

**Dependencies:**
- libft (bundled)

### Usage

**Normal mode:**

```bash
./pipex infile cmd1 cmd2 outfile
```

Equivalent shell expression:

```bash
< infile cmd1 | cmd2 > outfile
```

**Multiple pipes:**

```bash
./pipex infile cmd1 cmd2 cmd3 outfile
```

Equivalent shell expression:

```bash
< infile cmd1 | cmd2 | cmd3 > outfile
```

**here_doc mode:**

```bash
./pipex here_doc DELIMITER cmd1 cmd2 outfile
```

Equivalent shell expression:

```bash
cmd1 << DELIMITER | cmd2 >> outfile
```

Lines are read from stdin until a line matching `DELIMITER` is entered.
The output is **appended** to `outfile` rather than truncated.

---

## Known Limitations

- **Command parsing:** commands are split on spaces only. Quoted arguments
  (e.g. `"hello world"`) are not supported within a command string.
- **PATH unset, non-executable file:** when `PATH` is unset and a file exists in
  the current directory but is not executable, pipex exits 126, but doesn't attempt
  to re-execute it as a shell script, like bash.
- **Fixed arena buffer size:** the arena is limited to a 4KB buffer at the moment.
- **here-doc written directly to pipe:** limits the amount of data able to be
  handled to 64KB

---

## Algorithm and Data Structure

### Architecture Overview

The program encapsulates the entire execution environment within a single
`t_env` struct that is passed by pointer almost everywhere. This provides
a single place to track and clean up every resource.

```
t_env
├── t_arena    *data        — arena holding all parsed command string arrays and pointers to those
├── t_node     *node        — array of parsed command nodes (one per pipeline stage)
├── size_t      node_cnt    — number of pipeline stages
├── int         pipe_fd[2]  — current pipe (PIPEOUT=0 read, PIPEIN=1 write)
├── int         input_fd    — current stdin source (infile or pipe read end)
├── int         output_fd   — current stdout sink (outfile or pipe write end)
├── int         status      — final exit status
└── t_mode      mode        — DEFAULT or HERE_DOC
```

---

### Core Data Structure

Because memory is managed via an arena, `t_node` only needs to store an offset
index. The command arguments are parsed as string arrays, explicitly NULL-terminated
directly in the arena buffer, ready to be passed to `execve`.

```c
typedef struct s_node
{
	size_t	data_idx;
}	t_node;

typedef struct s_env
{
	t_arena	*data;
	t_node	*node;
	size_t	node_cnt;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	int		status;
	t_mode	mode;
}	t_env;
```

---

### Memory Management — Arena Allocator

Instead of managing individual `malloc` and `free` calls for every string and
array, the project uses a custom **Linear Arena Allocator** (`t_arena`).

- **Performance & cache locality:** a single large block is allocated at startup;
  subsequent allocations simply increment a pointer offset (`arena->used`).
- **Safety:** memory is freed all at once when the arena is destroyed, making
  leaks virtually impossible even during complex error exits or pipeline failures.
- **Efficient rollbacks:** `arena_save` and `arena_restore` allow the program to
  temporarily write strings to the arena (e.g. during path resolution) and rewind
  the pointer on failure, with no fragmentation.
- **Limitations:** The arena buffer is only 4 KB in size, there is no `arena_reinit()`
  that would increase the size of the arena, when it fills up.

---

### Parsing

`parse_to_nodes` iterates over the command arguments and fills each `t_node`:

- in `DEFAULT` mode, commands start at `argv[2]`;
- in `HERE_DOC` mode, commands start at `argv[3]` (after the delimiter).

Each command string is split on spaces via `arena_split` and stored in the arena
as a null-terminated `char **`. The resulting array is retrieved later by its
`data_idx` byte offset using `get_arena_ptr`.

---

### Execution and Piping

The core execution loop in `execute` processes each node sequentially:

1. `init_output_fd`: creates a pipe if this is not the last node, otherwise
   leaves `output_fd` as `-1` (the child opens the outfile itself).
2. `fork`: spawns the child process.
3. The parent calls `prepare_next_fds` to close its copy of the write end and
   store the read end as `input_fd` for the next iteration.

A final `wait` loop (`get_status`) handles `EINTR` interruptions, reaps all
children, and returns the exit status of the last child in the pipeline.

#### Child Setup

Each child calls `setup_fds` before executing:

1. If this is the last node, the child opens the outfile and assigns it to
   `env->output_fd`. Failure is reported but execution continues.
2. `handle_fds` dups `input_fd` -> `STDIN` and `output_fd` -> `STDOUT` if they
   are valid (`> -1`), and closes all pipe ends the child does not need.
3. `handle_fds` returns a non-zero value if either fd was `-1` (bad infile or
   bad outfile). The child then exits immediately without reaching `execve`,
   closing the write end of the pipe and sending EOF to the next child —
   matching bash's behaviour where a failed redirection lets the rest of the
   pipeline run with empty input rather than hanging.

#### Command Resolution

`get_cmd_path` resolves the command name to an executable path:

- if the name contains a `/`, it is used as-is;
- if `PATH` is unset, the command is looked up in `./`;
- otherwise, `find_in_path` iterates over the colon-separated directories
  in `PATH` and returns the first command path constructed with this entry
  where `access(path, F_OK) != -1`.

The path is constructed directly in the arena buffer; `arena_restore` rewinds
on each failed candidate with no allocations.

Existence is checked with `F_OK` only, not `X_OK`. If the file exists but is not
executable, it is passed to `execve` anyway, which then sets `errno = EACCES`.
This lets the program correctly distinguish 126 from 127:

```c
execve(cmd_path, cmd_argv, envp);
if (errno == ENOENT)
    pipex_exit(env, cmd_argv[0], "command not found", 127);
pipex_exit(env, cmd_argv[0], strerror(errno), 126);
```

#### Exit Codes

| Condition | Code |
| :-- | :-- |
| success | 0 |
| command not found | 127 |
| command exists but not executable | 126 |
| fork / pipe / dup2 failure | 1 |
| bad infile / outfile | 1 (error printed, pipeline continues) |

---

### here_doc

`read_here_doc` creates a pipe, reads lines from stdin with `get_next_line`,
and writes them to the write end until a line matching the delimiter is entered.
The read end is then stored as `env->input_fd`, making it the stdin source for
the first child exactly as a regular infile would be.

The output file is opened with `O_APPEND` instead of `O_TRUNC` in here_doc mode.

**Limitation:** here-docs is written directly to the pipe buffer, so it can only
handle 64KB of data before locking. I intend to improve this in `minishell`.

---

### Error Handling and Cleanup

Every system call (`open`, `pipe`, `fork`, `execve`, `dup2`) is strictly
validated. `pipex_cleanup` is the single cleanup path:

- frees the arena;
- frees the `t_node` array;
- flushes `get_next_line` static storage via `get_next_line(-255)`.

`pipex_exit` is the centralized exit funnel used on all error paths:

- closes any dangling file descriptors (`pipex_close_fds`);
- calls `pipex_cleanup`;
- prints bash-like error messages via `strerror(errno)`;
- exits with the appropriate status code.

`arena_hook_cleanup` registers `pipex_cleanup` with the arena so cleanup also
runs if the arena itself fails internally.

---

## Resources

### Documentation and References

- [`wait(2)`, `execve(2)`, `pipe(2)`, `dup2(2)`](https://man7.org/linux/man-pages/index.html)
- [`errno` codes](https://man7.org/linux/man-pages/man3/errno.3.html)
- [GNU bash source](https://git.savannah.gnu.org/cgit/bash.git)
- [Bash Reference Manual - Command, Search and Execution](https://www.gnu.org/software/bash/manual/bash.html#Command-Search-and-Execution)
- [Andrew Kelley: A Practical Guide to Applying Data Oriented Design (DoD)](https://youtu.be/IroPQ150F6c)
- [Casey Muratori | Smart-Pointers, RAII, ZII? Becoming an N+2 programmer](https://youtu.be/xt1KNDmOYqA)

### AI Usage

AI was used mainly for interactive rubber ducking and advanced search engine.
