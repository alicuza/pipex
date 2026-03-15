/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:40:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/15 19:45:18 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "arena.h"
# define SIZE 1024
# define STDIN 0
# define STDOUT 1
# define PIPEIN 1
# define PIPEOUT 0

typedef enum e_type
{
	ARG,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
}	t_type;

typedef struct s_node
{
	int		data_idx;
	int		size;
	int		sibling_idx;
	int		child_idx;
	t_type	type;
}	t_node;

typedef struct s_env
{
	t_arena	*data;
	t_node	*node;
	int		pipe_fd[2];
	int		node_cnt;
	int		input_fd;
	int		output_fd;
}	t_env;

#endif
