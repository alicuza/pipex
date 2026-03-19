/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:16:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/19 11:50:31 by sancuta          ###   ########.fr       */
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
	return (-1)
}

char	*get_cmd_path(t_env *env, char **argv, char *paths, int node_idx)
{
	int		i;
	int		save;
	int		len;
	char	*error;
	int		done;

	i = 0;
	while (paths[i])
	{
		done = 0;
		len = count_to_del(*src, del);
		if (len)
		{
			save = arena_save(env->data)
			offset = arena_strlcpy(env->data, paths[i], len + 1);
			env->data.used--;
			arena_strlcpy(env->data, env->node + node_idx, ft_strlen(env->node + node_idx));
			check_path(); // TODO maybe put everything in there
/*			errno = 0; // check how error handling should be here
			if (access(env->data[offset], F_OK) == -1)
			{
				error = strerror(err);
				write(2, "pipex: ", 7);
				write(2, error, ft_strlen(error));
				write(2, "\n", 1);
				env->last_status = 127;
				if (access(env->data[offset], F_OK | X_OK) == -1)
					env->last_status = 126;
				arena_restore(save);
			}
			else
			{
				env->last_status = 0;
			}
*/			i += len + 1;
		}
		else if (!done) // remove redundant checks, if there are multiple empty paths in PATH
		{
			save = arena_save(env->data)
			offset = arena_strlcpy(env->data, "./", 3);
			env->data.used--;
			arena_strlcpy(env->data, env->node + node_idx, ft_strlen(env->node + node_idx));
			check_path(); // TODO maybe put everything in there
/*			errno = 0; // check how error handling should be here
			if (access(env->data[offset], F_OK) == -1)
			{
				env->last_status = 127;
				if (access(env->data[offset], F_OK | X_OK) == -1)
					env->last_status = 126;
				arena_restore(save);
			}
			done = 1;
*/		}
	}
}

char	*get_cmd(t_env *env, size_t idx, char **envp)
{
	int		i;
	int		path_idx;
	char	*path;

	i = 0;
	path_idx = get_path_idx(envp);
	if (path_idx < 0) // no PATH in env
		return (env->data + arena_strlcpy(env->data, "./", 3));
	get_cmd_path(env, argv, envp[path_idx]);
	return (); // TODO:FINISH
}

inline int	is_child(int pid)
{
	return (!pid);
}

int	execute(t_env *env, int argc, char** argv, char **envp)
{
	int		pid;
	int		i;
	int		last_status;
	char	**cmd_argv;
	char	*cmd_path;

	i = 0;
	while(i < env->node_cnt)
	{
		cmd_argv = get_arena_ptr(env->data, env->node[i].data_idx);
		cmd_path = get_cmd_path(env, i, envp);
		init_output_fd(env, argc, argv);
		pid = fork();
		if (is_child(pid))
		{
			handle_fds(env);
			execve(cmd_path, cmd_argv, env);
		}
		prepare_next_fds(env);
		i++;
	}
	close(env->input_fd);
	return (last_status);
}

void	init_output_fd(t_env *env, int argc, char **argv)
{
		if (i == env->node_cnt - 1)
//			open_output(env, argc, argv); // maybe use this as a function to check for appending.
			env->output_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (env->output_fd < 0)
				handle_exit(env, EXIT_FAILURE, "init_outpt_fd couldn't open the path"); // appropriate return code
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
int	get_last_status(t_env *env, int pid)
{
	int	i;
	int status;

	i = 0;
	while (i < env->node_cnt)
		if (pid == wait(&status))
			last_status = status;
	return(last_status)
}
