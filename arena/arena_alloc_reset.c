/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/15 23:15:06 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "arena.h"

/*
 * natural alignment of 64bit systems
 */

static void	arena_align(t_arena *arena, size_t align)
{
	arena->used = (arena->used + (align - 1)) & ~(align - 1);
}

size_t	arena_alloc(void *env, t_arena *arena, size_t size, t_handle_exit_fn handle_exit)
{
	size_t	offset;

	arena_align(arena, sizeof(void *));
	if (size > (arena->cap - arena->used))
		handle_exit(env, EXIT_FAILURE, "aren_alloc: arena too small\n");
	offset = arena->used;
	arena->used += size;
	return (offset);
}
size_t	arena_array_alloc(t_arena *arena, size_t nbr, size_t size)
{
	size_t	offset;

	arena_align(arena, sizeof(void *));
	if (size && nbr > (arena->cap - arena->used) / size)
		handle_exit(env, EXIT_FAILURE, "aren_array_alloc: arena too small\n");
	offset = arena->buf + arena->used;
	arena->used += nbr * size;
	return (offset);
}

void	arena_reset(t_arena *arena)
{
	arena->used = sizeof(void *); // arena->buf[0-8] is a zero initialised stub.
}
