/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:37:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/11 11:47:28 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc < 5)
	{
		ft_printf("Error: too few arguments: usage: ./pipex [opt: \"here_doc\" LIMITER] infile cmd_1 cmd_2 [opt: cmd_3 ... cmd_n] outfile\n");
		return (1); // think of error codes
	}
	env->argc = argc;
	init_env(&env);
	parse_to_node(&env);
	execute_cmd(&env);
}

void	init_env(t_env *env, int argc, char **argv, char** envp)
{
	env = (t_env){0};
	env->arena = arena_init(SIZE);
	if (!env->arena)
		handle_exit(env, EXIT_FAILURE, "init_env1");
	env->output_fd = -1; // gets assigned in the cmd while loop
	init_nodes(env, argc);
}

void	init_nodes(t_env *env, int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		env->node_cnt = argc - 4;
		env->node = malloc(env->node_cnt * sizeof(t_node));
		if (!env->node)
			handle_exit(env, EXIT_FAILURE, "init_nodes1");
		env->input_fd = STDIN;
		env->del = argv[2];
	}
	else
	{
		env->node_cnt = argc - 3;
		env->node = malloc(env->node_cnt * sizeof(t_node));
		if (!env->node)
			handle_exit(env, EXIT_FAILURE, "init_nodes2");
		env->input_fd = open(argv[1], O_RDONLY); // checking whether this worked happens in the child
	}
}
