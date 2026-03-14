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
# define SIZE 1024
# define STDIN 0
# define STDOUT 1
# define PIPEIN 1
# define PIPEOUT 0

typedef enum e_type
{
	REDIR_IN,
	REDIR_OUT,
	NO_REDIR,
}	t_type;

typedef struct s_node
{
	size_t	argv_idx;
	size_t	nbr;
	t_type	type;
}	t_node;

typedef struct s_env
{
	t_arena	*arena;
	t_node	*node;
	int		*in_argc;
	char	**in_argv;
	char	**in_envp;
	int		pipe_fd[2];
	int		node_cnt;
	int		input_fd;
	int		output_fd;
}	t_env;

#endif
