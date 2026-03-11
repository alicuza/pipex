/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:40:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/11 10:38:50 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "arena.h"

typedef enum e_token
{
	TOK_NIL,
	TOK_AND,
	TOK_OR,
	TOK_PIPE,
	TOK_WORD,
	TOK_HERE_DOC,
	TOK_RED_IN,
	TOK_RED_OUT,
}	t_token;

typedef struct s_node
{
	t_token	type;
	size_t	data_idx;
	size_t	data_cnt;
	size_t	sibling_idx;
	size_t	child_idx;
}	t_node;

typedef struct s_env
{
	t_arena	node_arena;
	t_arena	string_arena;
	size_t	pipe_head;
}	t_env;
#endif
