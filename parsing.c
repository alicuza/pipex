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
#define WORD_DEL 32
#define PATH_DEL 58

size_t	get_start_idx(t_env *env)
{
	size_t start_idx;

	if (env->input_fd == STDIN)
	{
		env->node[0].type = HERE_DOC;
		start_idx = 3;
	}
	else
	{
		env->node[0].type = REDIR_IN;
		start_idx = 2;
	}
	return (start_idx);
}

void	parse_to_nodes(t_env *env, char **argv)
{
	size_t	start_idx;
	size_t	i;

	start_idx = get_start_idx(env);
	env->node[0].data_idx = arena_split(env->data, argv[start_idx], WORD_DEL);
	start_idx++;
	i = 0;
	while (++i < env->node_cnt - 1)
	{
		env->node[i].type = PIPE;
		env->node[i].data_idx = arena_split(env->data, argv[start_idx], WORD_DEL);
		start_idx++;
	}
	env->node[i].type = REDIR_OUT;
	env->node[i].data_idx = arena_split(env->data, argv[start_idx], WORD_DEL);
}
