#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define SIZE 3

int main(int argc, char** argv, char **env)
{
	int		pipe_fd[2];
	int		input_fd;	// last pipe's write end.
	int		output_fd;
	int		nbr_cmds = SIZE;
	int		child_pid;
	int		i;

	char	infile_path[] = "infile";
	char	outfile_path[] = "outfile";

	char	*cmd[3] = {
		"/usr/bin/cat",
		"/usr/bin/grep",
		"/usr/bin/wc",
	};
	char *args[3][3] = {
		{"cat", "-e", NULL},
		{"grep", "fane", NULL},
		{"wc", "-c", NULL},
	};

	input_fd = open(infile_path, O_RDONLY);
	i = 0;
	while(i < nbr_cmds)
	{
		if (i == nbr_cmds - 1)
			output_fd = open(outfile_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
		{
			pipe(pipe_fd);
			output_fd = pipe_fd[1];
		}
		child_pid = fork();
		if (!child_pid)
		{
			close(pipe_fd[0]);
			dup2(input_fd, 0);
			dup2(output_fd, 1);
			close(input_fd);
			close(output_fd);
			execve(cmd[i], args[i], env);
		}
		close (output_fd);
		close (input_fd);
		input_fd = pipe_fd[0];
		i++;
	}
	i = 0;
	while (i < nbr_cmds)
		waitpid(child_pid, NULL, 0);
	close(input_fd);
	return (0);
}
