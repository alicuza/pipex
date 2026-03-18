/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:16:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/18 19:31:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(t_env *env, int argc, char** argv, char **env)
{
	int		child_pid;
	int		i;

//	open_input(env, argv); // maybe use this as a function to check for here_doc
	env->input_fd = open(argv[1], O_RDONLY);
	i = 0;
	while(i < env->node_cnt)
	{
		child_pid = fork();
		if (!child_pid) // maybe an inline is_child() function check instead of this cryptic mess
		{
			close(env->pipe_fd[0]);
			dup2(env->input_fd, 0);
			dup2(env->output_fd, 1);
			close(env->input_fd);
			close(env->output_fd);
			execve(/*TODO*/get_cmd_path(i), get_arena_ptr(env->data, env->node[i].data_idx), env);
		}
		close(env->output_fd);
		close(env->input_fd);
		env->input_fd = env->pipe_fd[0];
		i++;
	}
	i = 0;
	while (i < env->node_cnt)
		waitpid(child_pid, NULL, 0);
	close(env->input_fd);
	return (0);
}

void	init_fd()
		if (i == env->node_cnt - 1)
//			open_output(env, argc, argv); // maybe use this as a function to check for appending.
			env->output_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
		{
			pipe(env->pipe_fd);
			env->output_fd = env->pipe_fd[1];
		}
