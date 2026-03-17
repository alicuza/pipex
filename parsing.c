/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:17:00 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/17 12:47:54 by sancuta          ###   ########.fr       */
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
		start_idx = 4;
	}
	return (start_idx);
}

size_t	get_cmdv_idx(t_arena *dest, size_t start_idx, size_t arg_cnt)
{
	size_t	offset;
	size_t	tmp_offset;
	size_t	i;
	char	*src;
	size_t	len;

	src = &dest->buf[start_idx];
	len = ft_strlen(src);
	offset = arena_memcpy(dest, src, (arg_cnt + 1) * sizeof(char *));
	tmp_offset = offset;
	i = -1;
	while (++i <= arg_cnt)
	{
		dest->buf[tmp_offset] = arena_memcpy(dest, src, len * sizeof(char));
		start_idx += len;
		src += len;
		tmp_offset += sizeof(char *);
	}
	return (offset);
}

void	parse_to_nodes(t_env *env, char **argv)
{
	size_t	start_idx;
	size_t	i;

	start_idx = get_start_idx(env);
	env->node[0].data_idx = get_cmdv_idx(env->data,
				arena_split(env->data, argv[start_idx], WORD_DEL),
				count_words(argv[start_idx], WORD_DEL));
	i = 0;
	while (++i < env->node_cnt - 1)
	{
		env->node[i].type = PIPE;
		env->node[i].data_idx = get_cmdv_idx(env->data,
				arena_split(env->data, argv[start_idx], WORD_DEL),
				count_words(argv[start_idx], WORD_DEL));
	}
	env->node[i].type = REDIR_OUT;
	env->node[i].data_idx = get_cmdv_idx(env->data,
			arena_split(env->data, argv[start_idx], WORD_DEL),
			count_words(argv[start_idx], WORD_DEL));
}
