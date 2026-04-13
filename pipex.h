/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:40:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/23 04:48:59 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "arena/arena.h"
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# define SIZE 4096
# define STDIN 0
# define STDOUT 1
# define PIPEIN 1
# define PIPEOUT 0
# define CMD_MISSING "command not found"

typedef enum e_mode
{
	DEFAULT,
	HERE_DOC,
}	t_mode;

typedef struct s_node
{
	size_t		data_idx;
}	t_node;

typedef struct s_env
{
	t_arena	*data;
	t_node	*node;
	size_t	node_cnt;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	int		status;
	t_mode	mode;
}	t_env;

void	parse_to_nodes(t_env *env, char **argv);
int		execute(t_env *env, int argc, char **argv, char **envp);
void	pipex_cleanup(void *env);
void	pipex_exit(t_env *env, char *name, char *message, int status);
int		handle_fds(t_env *env, size_t idx);
char	*get_cmd_path(t_env *env, char *path_var, int node_idx);
char	*get_path_var(char **envp);
void	init_output_fd(t_env *env, int argc, char **argv, size_t idx);
void	prepare_next_fds(t_env *env, size_t cnt);
int		get_outfile_flags(t_env *env);
#endif
