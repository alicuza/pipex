/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:41:15 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/22 17:55:09 by sancuta          ###   ########.fr       */
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
	{
		errno = 0;
		env->output_fd = open(argv[argc - 1], get_outfile_flags(env), 0644);
		if (env->output_fd < 0)
			handle_status_msg("pipex", argv[argc - 1], strerror(errno), 1);
	}
	else
	{
		if (pipe(env->pipe_fd) < 0)
			pipex_exit(env, argv[argc - 1], strerror(errno), 1);
		env->output_fd = env->pipe_fd[PIPEIN];
		env->pipe_fd[PIPEIN] = -1;
	}
}

void	handle_fds(t_env *env, size_t idx)
{
	if (idx != env->node_cnt - 1)
		close(env->pipe_fd[PIPEOUT]);
	errno = 0;
	if (dup2(env->input_fd, STDIN) < 0)
		pipex_exit(env, "dup2", strerror(errno), 1);
	errno = 0;
	if (dup2(env->output_fd, STDOUT) < 0)
		pipex_exit(env, "dup2", strerror(errno), 1);
	close(env->input_fd);
	env->input_fd = -1;
	close(env->output_fd);
	env->output_fd = -1;
}

void	prepare_next_fds(t_env *env, size_t cnt)
{
	close(env->output_fd);
	env->output_fd = -1;
	close(env->input_fd);
	env->input_fd = -1;
	if (cnt != env->node_cnt - 1)
	{
		env->input_fd = env->pipe_fd[PIPEOUT];
		env->pipe_fd[PIPEOUT] = -1;
	}
}
