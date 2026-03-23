/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:16:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/23 03:40:50 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_status(int pid)
{
	int		tmp;
	int		tmp_pid;
	int		status;

	status = 0;
	while (1)
	{
		tmp_pid = wait(&tmp);
		if (tmp_pid > 0)
		{
			if (tmp_pid == pid)
				status = tmp;
			continue ;
		}
		if (pid == -1 && errno == EINTR)
			continue ;
		break;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

void	setup_fds(t_env *env, size_t node_idx, int argc, char **argv)
{
	if (node_idx == env->node_cnt - 1)
	{
		errno = 0;
		env->output_fd = open(argv[argc - 1], get_outfile_flags(env), 0644);
		if (env->output_fd < 0)
			handle_status_msg("pipex", argv[argc - 1], strerror(errno), 1);
	}
	if (handle_fds(env, node_idx))
	{
		pipex_cleanup(env);
		exit(1);
	}
}

void	child_execute(t_env *env, int argc, char **argv, char **envp, size_t node_idx)
{
	char	**cmd_argv;
	char	*cmd_path;

	setup_fds(env, node_idx, argc, argv);
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
	if (errno == ENOENT)
		pipex_exit(env, cmd_argv[0], CMD_MISSING, 127);
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
		if (!pid)
			child_execute(env, argc, argv, envp, i);
		prepare_next_fds(env, i);
		i++;
	}
	return (get_status(pid));
}
