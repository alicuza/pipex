
#include "libft.h"

void	handle_exit(t_exit_data data)
{
	if (data.status)
	{
		ft_putstr_fd(data.prefix, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(data.name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(data.message, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(data.status);
}
