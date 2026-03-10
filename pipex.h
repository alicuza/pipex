/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:40:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/10 12:31:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_thing
{
	t_token	type;
	size_t	data_idx;
	size_t	data_cnt;
	size_t	sibling_idx;
	size_t	child_idx;
}	t_thing;

typedef struct s_env
{
	t_arena	nodes;
	t_arena	tmp;
	size_t	pipe_head;
}	t_env;

#endif
