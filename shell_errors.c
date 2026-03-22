/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:33:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/22 12:42:22 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/get_next_line.h"

void	pipex_cleanup(void *env)
{
	if (env)
	{
		arena_free(((t_env *)env)->data);
		free(((t_env *)env)->node);
	}
	get_next_line(-255);
}

void	pipex_close_fds(t_env *env)
{
	if (env->input_fd != -1)
	{
		close(env->input_fd);
		env->input_fd = -1;
	}
	if (env->output_fd != -1)
	{
		close(env->output_fd);
		env->output_fd = -1;
	}
	if (env->pipe_fd[PIPEOUT] != -1)
	{
		close(env->pipe_fd[PIPEOUT]);
		env->pipe_fd[PIPEOUT] = -1;
	}
	if (env->pipe_fd[PIPEIN] != -1)
	{
		close(env->pipe_fd[PIPEIN]);
		env->pipe_fd[PIPEIN] = -1;
	}
}

void	pipex_exit(t_env *env, char *name, char *message, int status)
{
	handle_exit_msg("pipex", name, message, status);
	pipex_close_fds(env);
	pipex_cleanup(env);
	exit(status);
}
