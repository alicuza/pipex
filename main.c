/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:37:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/15 22:31:12 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc < 5)
	{
		ft_printf("Error: too few arguments: usage: ./pipex [opt: \"here_doc\"
				LIMITER] infile cmd_1 cmd_2 [opt: cmd_3 ... cmd_n] outfile\n");
		return (1); // think of error codes or better yet, include errno and use it?
	}
	init_env(&env, argc, argv, envp);
	parse_to_nodes(&env, argv);
	execute_cmd(&env);
}

void	init_env(t_env *env, int argc, char **argv, char** envp)
{
	env = (t_env){0};
	env->data = arena_init(env, SIZE, &handle_exit);
	env->output_fd = -1; // gets assigned in the cmd while loop
	init_nodes(env, argc);
}

// decided against having a zero initialised stub at env->nodes[0] to return on failure,
// because there are no allocations happening after the initialisation
void	init_nodes(t_env *env, int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		env->node_cnt = argc - 4;
		env->node = malloc(env->node_cnt * sizeof(t_node));
		if (!env->node)
			handle_exit(env, EXIT_FAILURE, "init_nodes1: malloc failed bro");
		env->input_fd = STDIN;
		env->del = argv[2];
	}
	else
	{
		env->node_cnt = argc - 3;
		env->node = malloc(env->node_cnt * sizeof(t_node));
		if (!env->node)
			handle_exit(env, EXIT_FAILURE, "init_nodes2: malloc failed bro");
		env->input_fd = open(argv[1], O_RDONLY); // checking whether this worked happens in the child
	}
}
