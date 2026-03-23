/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:41:15 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/23 02:54:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_outfile_flags(t_env *env)
{
	if (env->mode == HERE_DOC)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (O_CREAT | O_WRONLY | O_TRUNC);
}

void	init_output_fd(t_env *env, int argc, char **argv, size_t idx)
{
	if (idx == env->node_cnt - 1)
		return ;
	if (pipe(env->pipe_fd) < 0)
		pipex_exit(env, argv[argc - 1], strerror(errno), 1);
	env->output_fd = env->pipe_fd[PIPEIN];
	env->pipe_fd[PIPEIN] = -1;
}

int	handle_fds(t_env *env, size_t idx)
{
	int	infile_status;
	int	outfile_status;

	infile_status = (idx == 0 && env->input_fd == -1);
	outfile_status = (idx == env->node_cnt - 1 && env->output_fd == -1);
	if (idx != env->node_cnt - 1)
		close(env->pipe_fd[PIPEOUT]);
	if (env->input_fd > -1)
	{
		errno = 0;
		if (dup2(env->input_fd, STDIN) < 0)
			pipex_exit(env, "dup2", strerror(errno), 1);
		close(env->input_fd);
		env->input_fd = -1;
	}
	if (env->output_fd > -1)
	{
		errno = 0;
		if (dup2(env->output_fd, STDOUT) < 0)
			pipex_exit(env, "dup2", strerror(errno), 1);
		close(env->output_fd);
		env->output_fd = -1;
	}
	return (infile_status || outfile_status);
}

void	prepare_next_fds(t_env *env, size_t cnt)
{
	if (env->output_fd > -1)
	{
		close(env->output_fd);
		env->output_fd = -1;
	}
	if (env->input_fd > -1)
	{
		close(env->input_fd);
		env->input_fd = -1;
	}
	if (cnt != env->node_cnt - 1)
	{
		env->input_fd = env->pipe_fd[PIPEOUT];
		env->pipe_fd[PIPEOUT] = -1;
	}
}
