/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:37:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/11 11:47:28 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	init_env(&env);
	lex();
	parse();
	ft_split();
}

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
