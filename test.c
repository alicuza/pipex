#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	int p1[2];
	int p2[2];
	int infile;
//	int outfile;
	int child_pid;
	char buf1[20] = {0};
	char buf2[20] = {0};
	char out[20] = {0};
	size_t len = 20;

	infile = open("infile", O_RDONLY);
//	outfile = open("outfile", O_WRONLY | O_CREAT, 0644);
	pipe(p1);
	child_pid = fork();
	if (!child_pid)
	{
		dup2(infile, 0);
		dup2(p1[1], 1);
		close(infile);
		close(p1[0]);
		close(p1[1]);
		read(0, buf1, len);
		write(1, buf1, len);
		return 0;
	}
	close(infile);
	close(p1[1]);
	pipe(p2);
	child_pid = fork();
	if (!child_pid)
	{
		dup2(p1[0], 0);
		dup2(p2[1], 1);
		close(p2[0]);
		close(p2[1]);
		read(0, buf2, len);
		write(1, buf2, len);
		return 0;
	}
	close(p1[0]);
	close(p2[1]);
//	dup2(p2[0], 0);
//	dup2(outfile, 1);
	waitpid(-1, NULL, 0);
	read(p2[0], out, len);
//	write(outfile, out, len);
	write(1, out, len);
	close(p2[0]);
	return 0;
}
