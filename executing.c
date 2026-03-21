/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:16:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 12:00:28 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	check_path(char *path)
{
	return (access(path, F_OK | X_OK) == -1);
}

static size_t	get_prefix(t_arena *data, char *path_var, int env_off, int size)
{
	size_t	offset;

	if (!path_var || !size)
		return (arena_strlcpy(data, "./", 3));
	offset = arena_strlcpy(data, path_var + env_off, size + 1);
	if (data->buf[data->used - 2] != '/')
	{
		data->used--;
		arena_strlcpy(data, "/", 2);
	}
	data->used--;
	return (offset);
}
char	*find_in_path(t_arena *data, char *path_var, char *cmd)
{
	int		size;
	int		env_off;
	size_t	offset;

	env_off = 5;
	size = ft_indchr(path_var + env_off, ':');
	if (size == -1)
		size = ft_strlen(path_var + env_off);
	while (*path_var)
	{
		offset = get_prefix(data, path_var, env_off, size);
		arena_strlcpy(data, cmd, ft_strlen(cmd) + 1);
		if(!check_path(data->buf + offset))
			break ;
		arena_restore(data, offset);
		if (path_var[env_off + size] == '\0')
			break ;
		env_off += size + 1;
		size = ft_indchr(path_var + env_off, ':');
		if (size == -1)
			size = ft_strlen(path_var + env_off);
	}
	return (data->buf + offset);
}

char	*get_cmd_path(t_env *env, char *path_var, int node_idx)
{
	size_t	offset;
	char	**cmdv;

	cmdv = (char **)(env->data->buf + env->node[node_idx].data_idx);
	if (!cmdv[0])
		return (NULL);
	if (ft_strchr(cmdv[0], '/'))
		return (cmdv[0]);
	if (!path_var)
	{
		offset = get_prefix(env->data, NULL, 0, 0);
		arena_strlcpy(env->data, cmdv[0], ft_strlen(cmdv[0]) + 1);
		return (env->data->buf + offset);
	}
	return (find_in_path(env->data, path_var, cmdv[0]));
}

static int	get_outfile_flags(t_env *env)
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
			env->exit_data = (t_exit_data){"pipex", argv[argc - 1], strerror(errno), 1};
			pipex_cleanup(env);
		}
	}
	else
	{
		pipe(env->pipe_fd);
		env->output_fd = env->pipe_fd[1];
	}
}

void handle_fds(t_env *env, size_t i)
{
	if (i != env->node_cnt - 1)
		close(env->pipe_fd[0]);
	dup2(env->input_fd, 0);
	dup2(env->output_fd, 1);
	close(env->input_fd);
	close(env->output_fd);
}

void prepare_next_fds(t_env *env)
{
	close(env->output_fd);
	close(env->input_fd);
	env->input_fd = env->pipe_fd[0];
}

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
	return(status);
}

int	is_child(int pid)
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
		env->exit_data = (t_exit_data){"pipex", "", CMD_NOT_FOUND, 127};
		pipex_cleanup(env);
	}
	cmd_path = get_cmd_path(env, get_path_var(envp), node_idx);
	if (!cmd_path)
	{
		env->exit_data = (t_exit_data){"pipex", cmd_argv[0], CMD_NOT_FOUND, 127};
		pipex_cleanup(env);
	}
	errno = 0;
	execve(cmd_path, cmd_argv, envp);
	env->exit_data = (t_exit_data){"pipex", cmd_argv[0], strerror(errno), 126};
	pipex_cleanup(env);
}

int	execute(t_env *env, int argc, char** argv, char **envp)
{
	int		pid;
	size_t	i;

	i = 0;
	while(i < env->node_cnt)
	{
		errno = 0;
		init_output_fd(env, argc, argv, i);
		pid = fork();
		if (is_child(pid))
			child_execute(env, envp, i);
		prepare_next_fds(env);
		i++;
	}
	return (get_status(pid));
}
