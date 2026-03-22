/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:36:13 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/22 12:21:57 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "../libft/libft.h"

t_arena	arena_init(size_t size)
{
	t_arena	arena;

	arena = (t_arena){0};
	if (!size)
		return (arena);
	arena.buf = /*malloc(size)*/NULL;
	if (!arena.buf)
		return (arena);
	ft_memset(arena.buf, 0, size);
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

void	arena_hook_cleanup(t_arena *arena, void (*clean)(void *), void *env) // am i using this?
{
	arena->clean = clean;
	arena->env = env;
}
