/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:16:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/20 16:31:31 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path_idx(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (i);
		i++;
	}
	return (-1);
}

int	check_path(t_env *env, char *path)
{
	if (access(path, F_OK) == -1)
	{
		write(2, "pipex: error1\n", 14);
		env->exit_status = 127;
	}
	else if (access(path, X_OK) == -1)
	{
		write(2, "pipex: error2\n", 14);
		env->exit_status = 126;
	}
	return (env->exit_status);
}

char	*get_cmd_path(t_env *env, char **envp, int node_idx)
{
	int		i;
	int		size;
	size_t	offset;
	char	**cmdv;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	size = ft_indchr(envp[i] + 5, ':'); // +5 to skip "PATH="
	while (1)
	{
		cmdv = (char **)(env->data->buf + env->node[node_idx].data_idx);
		if (size <= 0)
			offset = arena_strlcpy(env->data, "./", 3);
		else
			offset = arena_strlcpy(env->data, envp + i, size);
		env->data->used--; // maybe add this to arena_strlcpy as arena_strlcat
		arena_strlcpy(env->data, cmdv[0], ft_strlen(cmdv[0]));
		if(check_path(env, env->data->buf + offset))
			break ;
		arena_restore(env->data, offset);
		size = ft_indchr(envp[i] + size, ':');
	}
	return (env->data->buf + offset);
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

void handle_fds(t_env *env)
{
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

int	get_status(t_env *env, int pid)
{
	int		tmp;
	int		status;
	size_t	i;

	i = 0;
	while (i < env->node_cnt)
		if (pid == wait(&tmp))
			status = tmp;
	return(status);
}
/*
char	*get_cmd(t_env *env, size_t idx, char **envp)
{
	int		i;
	int		path_idx;
	char	*path;

	i = 0;
	path_idx = get_path_idx(envp);
	if (path_idx < 0) // no PATH in env
		return (env->data->buf + arena_strlcpy(env->data, "./", 3));
	get_cmd_path(env, argv, envp[path_idx]);
	return (); // TODO:FINISH
}
*/
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
		cmd_path = get_cmd_path(env, envp, i);
		init_output_fd(env, argc, argv, i);
		pid = fork();
		if (is_child(pid))
		{
			handle_fds(env);
			execve(cmd_path, cmd_argv, envp);
		}
		prepare_next_fds(env);
		i++;
	}
	close(env->input_fd);
	return (get_status(env, pid));
}

