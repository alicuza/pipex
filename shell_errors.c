/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:33:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 21:34:07 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_cleanup(void *env)
{
	t_env	*e;

	e = (t_env *)env;
	if (e)
	{
		arena_free(e->data);
		free(e->node);
	}
}

void	pipex_exit(t_env *env, char *name, char *message, int status)
{
	pipex_cleanup(env);
	handle_exit("pipex", name, message, status);
}
