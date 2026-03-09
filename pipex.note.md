# bash
## commands
**soft linking**
- to create link: `ln -s path/to/target/ link_name`
- to remove link: `rm link_name`
- to overwrite existing link: `ln -sf /path/to/new_target existing_link_name`
- to check where a link points to: `ls -l link_name` will produce something like: `link_name -> /path/to/target`
**changing directories**
- `pushd path/to/target` changes the current working directory to `target` and pushes the last one to a stack.
- `popd` changes to the top working directory of the stack and removes it from the stack.
## behaviour
**PATH**
if a command is not found in PATH, bash looks for `function command_not_found_handle()` and executes it, otherwise it returns an error: [https://www.gnu.org/software/bash/manual/bash.html#Command-Search-and-Execution](Bash Reference Manual - Command, Search and Execution).
**PARSING**
[https://mywiki.wooledge.org/BashParser](Bash Parsing).
# git
## commands
**create remote repo from cli for gitlab.com**
```bash
git init
git add .
git commit -m "Initial commit"
git branch -M main
git remote add origin git@gitlab.com:USERNAME/REPO_NAME.git
//git remote add origin https://gitlab.com/USERNAME/REPO_NAME.git // for https access
git push -u origin main
```
- `origin` & `main` being arbitrary default names.

# workflow
**accessibility**
- link your current working project folders into your `~` for easier access.
**testing**
- use `nm -u command` to check what functions are being called from libraries? // TODO: read up on this

# man
`man 2` - Linux Programmer's Manual
`man 3` - POSIX Programmer's Manual

# C
**function pointers**
- you can typedef a function or function pointer in the following way: 
```c
typedef return_type (new_function_type)(function_param_type1, ...) // fnct
typedef return_type (*new_function_type)(function_param_type1, ...) // fnct ptr
```
**strategies to make structs lean**
[https://youtu.be/IroPQ150F6c](Andrew Kelley: A Practical Guide to Applying Data Oriented Design (DoD))
[https://youtu.be/xt1KNDmOYqA](Casey Muratori | Smart-Pointers, RAII, ZII? Becoming an N+2 programmer)

**intrusive list**
[https://youtu.be/ShSGHb65f3M?si=QtZeka9lb9zKuevv&t=32](Avoiding Modern C++ | Anton Mikhailov - Wookash Podcast)
-> [https://youtu.be/ShSGHb65f3M?si=xy3uTsOZVL8VoSfY&t=5541](ex. what it can be very useful for)

**user input**
[https://youtu.be/ShSGHb65f3M?si=Owx_yWyx1AmNGvfL&t=6660](user input trick for opposing directions)

## arenas
### funcitons
```c
arena_init()	// allocate the backing buffer (malloc once)
arena_alloc()	// bump the pointer, align, return a pointer
arena_reset()	// set used back to 0, reuse the buffer
//arena_save()	// save used for scratch patterns
//arena_restore()	// restore used for scratch patterns
arena_free()	// free the backing buffer
```
### alignment
```c
arena->used = (arena->used + 7) & ~7;	// aligning the next allocation position to 8 bytes.
```

**examples**
```
used = 13  →  13 + 7 = 20  →  20 & ~7 = 16
used = 16  →  16 + 7 = 23  →  23 & ~7 = 16
used = 17  →  17 + 7 = 24  →  24 & ~7 = 24
```

`~7` rounds to the 8-byte boundary.
