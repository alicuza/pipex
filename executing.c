/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:16:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/20 22:13:49 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	check_path(char *path)
{
	return (access(path, F_OK | X_OK) == -1);
}

char	*get_cmd_path(t_env *env, char *path_var, int node_idx)
{
	int		size;
	int		env_off;
	size_t	offset;
	char	**cmdv;

	env_off = 5;
	size = ft_indchr(path_var + env_off, ':'); // +5 to skip "PATH="
	while (path_var + env_off)
	{
		cmdv = (char **)(env->data->buf + env->node[node_idx].data_idx);
		if (size <= 0)
			offset = arena_strlcpy(env->data, "./", 3);
		else
		{
			offset = arena_strlcpy(env->data, path_var + env_off, size + 1);
			if(env->data->buf[env->data->used - 2] != '/')
			{
				env->data->used--;
				arena_strlcpy(env->data, "/", 2);
			}
		}
		env->data->used--; // maybe add this to arena_strlcpy as arena_strlcat
		arena_strlcpy(env->data, cmdv[0], ft_strlen(cmdv[0]) + 1);
		if(!check_path(env->data->buf + offset))
			break ;
		ft_printf("testing PATH: %s\n", path_var); // delete this, only for debugging
		ft_printf("testing path: %s\n", env->data->buf + offset); // delete this, only for debugging
		arena_restore(env->data, offset);
		env_off += size + 1;
		ft_printf("next command at index: %d\n", env_off); // delete this, only for debugging
		size = ft_indchr(path_var + env_off, ':');
		ft_printf("next ':' is so much further: %d\n", size); // delete this, only for debugging
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

int	get_status(t_env *env, int pid)
{
	int		tmp;
	int		tmp_pid;
	int		status;
	size_t	i;

	i = -1;
	while (++i < env->node_cnt)
	{
		tmp_pid = wait(&tmp);
		if (tmp_pid == pid)
			status = tmp;
		else if (tmp_pid < 0)
			break ;
	}
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
	return (get_status(env, pid));
}

