/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:17:00 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/20 23:51:36 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	get_start_idx(t_env *env)
{
	if (env->mode == HERE_DOC)
		return (3);
	return (2);
}

void	parse_to_nodes(t_env *env, char **argv)
{
	size_t	start_idx;
	size_t	i;

	start_idx = get_start_idx(env);
	env->node[0].data_idx = arena_split(env->data, argv[start_idx], ' ');
	start_idx++;
	i = 0;
	while (++i < env->node_cnt - 1)
	{
		env->node[i].data_idx = arena_split(env->data, argv[start_idx], ' ');
		start_idx++;
	}
	env->node[i].data_idx = arena_split(env->data, argv[start_idx], ' ');
}
