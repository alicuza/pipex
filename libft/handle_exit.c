/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:24:18 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/22 11:37:36 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_exit_msg(char *prefix, char *name, char *message, int status)
{
	if (status)
	{
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
}
