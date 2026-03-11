/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:36:13 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 11:29:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include <unistd.h>

t_arena	arena_init(size_t size)
{
	t_arena	arena;

	arena = (t_arena){0};
	arena.buf = malloc(size);
	ft_memset(arena.buf, 0, size);
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
