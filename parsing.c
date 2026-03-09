/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:17:00 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 13:23:35 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "arena.h"

// pass argc or argc-1 from main and handle accordingly

int	handle_args(t_arena *arena, int argc, const char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		parse_cmd(argv[i]);
	}
	return (0);
}

int	parse_cmd(t_arena *arena, const char *arg)
{
	int	idx;

	idx = ft_indchr(arg, ' ');
	ft_strdup()
	return (0);
}
