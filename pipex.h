/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:40:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/20 21:40:22 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "arena/arena.h"
# include <fcntl.h>
# include <sys/wait.h>
# define SIZE 4096
# define STDIN 0
# define STDOUT 1
# define PIPEIN 1
# define PIPEOUT 0

typedef enum e_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
}	t_type;

typedef struct s_node
{
	size_t		data_idx;
	size_t		arg_cnt;
	t_type	type;
}	t_node;

typedef struct s_env
{
	t_arena	*data;
	t_node	*node;
	size_t	hd_del_idx;
	size_t	node_cnt;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	int		exit_status;
}	t_env;

size_t	word_len(const char *s, char del); // SHOULD BE IN LIBFT
size_t	count_words(const char *s, char del); // MOVE TO LIBFT
void	*ft_print_memory(void *addr, unsigned int size); // MOVE TO LIBFT
//void	handle_exit(t_env *env, int status, char *message);
void	parse_to_nodes(t_env *env, char **argv);
int		execute(t_env *env, int argc, char** argv, char **envp);
#endif
