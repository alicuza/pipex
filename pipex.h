/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:40:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/16 15:13:15 by sancuta          ###   ########.fr       */
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
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	HERE_DOC,
}	t_type;

typedef struct s_node
{
	size_t		data_idx;
	size_t		arg_cnt;
	size_t		next_idx;
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

size_t	get_cmdv(t_arena *dest, size_t start_idx, size_t arg_cnt);
#endif
