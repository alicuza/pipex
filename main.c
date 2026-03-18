/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:37:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/18 10:58:06 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// decided against having a zero initialised stub at env->nodes[0] to return on failure,
// because there are no allocations happening after the initialisation
void	init_nodes(t_env *env, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		env->node_cnt = argc - 4;
		env->node = malloc(env->node_cnt * sizeof(t_node));
		if (!env->node)
			handle_exit(EXIT_FAILURE, "init_nodes1: malloc failed bro");
		env->input_fd = STDIN;
		env->hd_del_idx = 2;
	}
	else
	{
		env->node_cnt = argc - 3;
		env->node = malloc(env->node_cnt * sizeof(t_node));
		if (!env->node)
			handle_exit(EXIT_FAILURE, "init_nodes2: malloc failed bro");
		env->input_fd = open(argv[1], O_RDONLY); // checking whether this worked happens in the child
	}
}

t_env	init_env(int argc, char **argv, char** envp)
{
	(void) envp; // for testing, as of now unused
	t_env	env;

	env = (t_env){0};
	env.output_fd = -1; // gets assigned in the cmd while loop
	init_nodes(&env, argc, argv);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_arena	arena;

	if (argc < 5)
	{
		ft_printf("Error: too few arguments:\nusage: ./pipex [opt: \"here_doc\" LIMITER] infile cmd_1 cmd_2 [opt: cmd_3 ... cmd_n] outfile\n");
		return (1); // think of error codes or better yet, include errno and use it?
	}
	arena = arena_init(SIZE);
	env = init_env(argc, argv, envp);
	env.data = &arena;
	parse_to_nodes(&env, argv);
	ft_print_memory(env.data->buf, env.data->cap);
}
