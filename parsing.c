/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:17:00 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/15 20:27:29 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "arena.h"

int	parse_to_nodes(t_env *env, char **argv)
{
	int	idx;
	int	i;
	int	cmd_idx;

	env->node[0].type = REDIR_IN;
	env->node[0].data_idx = argv_to_arena(env->data, cmd_idx);
	;
	i = 0;
	while (++i < env->node_cnt - 1)
	{
			
	}
	env->node[i].type = REDIR_OUT;
	env->node[0].data_idx = env->data.used;
	return (0);
}
