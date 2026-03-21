
#include "pipex.h"
#include <string.h>
#include <errno.h>

char	*shell_strerror(int err)
{
	if (error == ENOENT)
		return ("No such file or directory");
	if (error == EACCES)
		return ("Permission denied");
	if (error == EISDIR)
		return ("Is a directory");
	return (strerror(err));
}

void	ft_perror(char *name)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(shell_strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
