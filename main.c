#define NBRC 3
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
//extern char **environ; //TODO read up on what can get passed to main, and which approach is better, takeing the environment as an argument to main or as an external variable.

int	main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	int		status;
	int		pipefd[NBRC + 1][2];
	int		child_pid[NBRC];
	char	*cmd_path[NBRC] = {
		"/usr/bin/cat",
		"/usr/bin/gret",
		"/usr/bin/wc",
	};
	char *arg[NBRC][3] = {
		{"cat", "-e", NULL},
		{"gret", "fane", NULL},
		{"wc", "-c", NULL},
	};
	int		i;
	int		j;

	pipefd[0][0] = open("infile", O_RDONLY);
	pipefd[0][1] = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	i = 1;
	while (i <= NBRC)
	{
		pipe(pipefd[i]);
		child_pid[i - 1] = fork();
		if (!child_pid[i - 1])
		{
			dup2(pipefd[i - 1][0], 0);
			dup2(pipefd[i % NBRC][1], 1);
			j = 0;
			while (j < i)
			{
				close(pipefd[j][0]);		// write end of stdin pipe
				close(pipefd[j][1]);		// other end of newly created pipe
				j++;
			}
			execve(cmd_path[i - 1], arg[i - 1], environ);
		}
		close(pipefd[i - 1][0]);
		close(pipefd[i - 1][1]);
		i++;
	}

	i = 0;
	while (i <= NBRC)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}

	i = 0;
	while (i < NBRC)
	{
		waitpid(child_pid[i], &status, 0);
		i++;
	}
	return (status); //TODO figure out return value
}
