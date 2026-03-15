/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:36:13 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/15 23:14:27 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include <unistd.h>

t_arena	arena_init(void *env, size_t size, t_handle_exit_fn handle_exit)
{
	t_arena	arena;

	arena = (t_arena){0};
	errno = 0; // dont't forget about this bad boy
	arena.buf = malloc(size + 8);
	if (!arena.buf)
		handle_exit(env, EXIT_FAILURE, "arena_init: malloc failed bro\n");
	ft_memset(arena.buf, 0, size);
	arena.used = 8; // arena.buf[0], if cast as a pointer, holds a NULL
	if (arena.buf)
		arena.cap = size;
	return (arena);
}

void	arena_free(t_arena *arena)
{
	free(arena->buf);
	arena->buf = NULL;
	arena->used = 0;
	arena->cap = 0;
}
