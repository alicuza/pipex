/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:41:15 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 21:42:57 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_outfile_flags(t_env *env)
{
	if (env->mode == HERE_DOC)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (O_CREAT | O_WRONLY | O_TRUNC);
}

void	init_output_fd(t_env *env, int argc, char **argv, size_t i)
{
	if (i == env->node_cnt - 1)
	{
		errno = 0;
		env->output_fd = open(argv[argc - 1], get_outfile_flags(env), 0644);
		if (env->output_fd < 0)
		{
			env->exit_data = (t_exit_data){"pipex", argv[argc - 1],
				strerror(errno), 1};
			pipex_cleanup(env);
		}
	}
	else
	{
		pipe(env->pipe_fd);
		env->output_fd = env->pipe_fd[1];
	}
}

void	handle_fds(t_env *env, size_t i)
{
	if (i != env->node_cnt - 1)
		close(env->pipe_fd[0]);
	dup2(env->input_fd, 0);
	dup2(env->output_fd, 1);
	close(env->input_fd);
	close(env->output_fd);
}

void	prepare_next_fds(t_env *env)
{
	close(env->output_fd);
	close(env->input_fd);
	env->input_fd = env->pipe_fd[0];
}
