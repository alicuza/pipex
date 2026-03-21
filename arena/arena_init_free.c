/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:36:13 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/18 11:00:36 by sancuta          ###   ########.fr       */
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
	arena.buf = malloc(size);
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

void	arena_hook_cleanup(t_arena *arena, void (*clean)(void *), void *env)
{
	arena->clean = clean;
	arena->env = env;
}
