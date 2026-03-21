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
		if (ft_strncmp(envp[i], "PATH=", 5))
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
		get_prefix(env->data, path_var, env_off, size);
		arena_strlcpy(env->data, cmdv[0], ft_strlen(cmdv[0]) + 1);
		if(!check_path(env->data->buf + offset))
			break ;
		arena_restore(env->data, offset);
		if (path_var[env_off + size] == '\0')
			break ;
		env_off += size + 1;
		size = ft_indchr(path_var + env_off, ':');
		if (size == -1)
			size = ft_strlen(path_var + env_off);
	}
	return (env->data->buf + offset);
}

char	*get_cmd_path(t_env *env, char *path_var, int node_idx)
{
	size_t	offset;
	char	**cmdv;

	cmdv = (char **)(env->data->buf + env->node[node_idx].data_idx);
	if (ft_strchr(cmdv[0], '/'))
		return (cmdv[0]);
	if (!path_var)
	{
		offset = build_prefix(env->data, NULL, 0, 0);
		arena_strlcpy(env->data, cmdv[0], ft_strlen(cmdv[0]) + 1);
		return (env->data->buf + offset);
	}
	return (find_in_path(env->data, path_var, cmdv[0]));
}

void	init_output_fd(t_env *env, int argc, char **argv, size_t i)
{
	if (i == env->node_cnt - 1)
	{
//		open_output(env, argc, argv); // maybe use this as a function to check for appending.
		env->output_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (env->output_fd < 0)
			handle_exit(EXIT_FAILURE, "init_outpt_fd couldn't open the path"); // appropriate return code
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

int	execute(t_env *env, int argc, char** argv, char **envp)
{
	int		pid;
	char	**cmd_argv;
	char	*cmd_path;
	size_t	i;

	i = 0;
	while(i < env->node_cnt)
	{
		cmd_argv = get_arena_ptr(env->data, env->node[i].data_idx);
		if ()
		cmd_path = get_cmd_path(env, get_path_var(envp), i);
		init_output_fd(env, argc, argv, i);
		pid = fork();
		if (is_child(pid))
		{
			handle_fds(env, i);
			execve(cmd_path, cmd_argv, envp);
		}
		prepare_next_fds(env);
		i++;
	}
	return (get_status(pid));
}
