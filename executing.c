/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:16:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 23:33:27 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_status(int pid)
{
	int		tmp;
	int		tmp_pid;
	int		status;

	status = 0;
	tmp_pid = wait(&tmp);
	while (tmp_pid > 0)
	{
		if (tmp_pid == pid)
			status = tmp;
		tmp_pid = wait(&tmp);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

static inline int	is_child(int pid)
{
	return (!pid);
}

void	child_execute(t_env *env, char **envp, size_t node_idx)
{
	char	**cmd_argv;
	char	*cmd_path;

	handle_fds(env, node_idx);
	cmd_argv = get_arena_ptr(env->data, env->node[node_idx].data_idx);
	if (!cmd_argv[0])
	{
		pipex_exit(env, "", CMD_MISSING, 127);
	}
	cmd_path = get_cmd_path(env, get_path_var(envp), node_idx);
	if (!cmd_path)
	{
		pipex_exit(env, cmd_argv[0], CMD_MISSING, 127);
	}
	errno = 0;
	execve(cmd_path, cmd_argv, envp);
	pipex_exit(env, cmd_argv[0], strerror(errno), 126);
}

int	execute(t_env *env, int argc, char **argv, char **envp)
{
	int		pid;
	size_t	i;

	i = 0;
	while (i < env->node_cnt)
	{
		errno = 0;
		init_output_fd(env, argc, argv, i);
		pid = fork();
		if (pid == -1)
			pipex_exit(env, "fork", strerror(errno), 1);
		if (is_child(pid))
			child_execute(env, envp, i);
		prepare_next_fds(env, i);
		i++;
	}
	return (get_status(pid));
}
