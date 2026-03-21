/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:37:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 21:33:12 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/get_next_line.h"

void	read_here_doc(t_env *env, char *del)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		pipex_exit(env, "pipe", strerror(errno), 1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(1);
		if (!line)
			break ;
		if (!ft_strncmp(line, del, ft_strlen(del))
			&& line[ft_strlen(del)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	env->input_fd = pipe_fd[0];
}

/*	decided against having a zero initialised stub at env->nodes[0]
	to return on failure, because there are no allocations happening
	after the initialisation
*/

void	init_nodes(t_env *env, int argc, char **argv)
{
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		env->node_cnt = argc - 4;
		env->input_fd = STDIN;
		read_here_doc(env, argv[2]);
	}
	else
	{
		env->node_cnt = argc - 3;
		errno = 0;
		env->input_fd = open(argv[1], O_RDONLY);
		if (env->input_fd == -1)
			pipex_exit(env, argv[1], strerror(errno), 1);
	}
	errno = 0;
	env->node = malloc(env->node_cnt * sizeof(t_node));
	if (!env->node)
		pipex_exit(env, "malloc", strerror(errno), 1);
}

t_env	init_env(int argc, char **argv)
{
	t_env	env;

	env = (t_env){0};
	env.output_fd = -1;
	init_nodes(&env, argc, argv);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_arena	arena;

	if (argc < 5)
		handle_exit("pipex", "main",
			"usage: ./pipex infile cmd_1 cmd_2 outfile", 1);
	errno = 0;
	arena = arena_init(SIZE);
	if (!arena.buf)
		handle_exit("pipex", "arena_init", strerror(errno), 1);
	env = init_env(argc, argv);
	env.data = &arena;
	arena_hook_cleanup(env.data, &pipex_cleanup, &env);
	parse_to_nodes(&env, argv);
	env.exit_data.status = execute(&env, argc, argv, envp);
	pipex_cleanup(&env);
	handle_exit(NULL, NULL, NULL, 0);
}
