/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 11:29:33 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "arena.h"

/*
 * natural alignment of 64bit systems
 */

static void	arena_align(t_arena *arena)
{
	arena->used = (arena->used + 7) & ~7;
}

size_t	arena_alloc(t_arena *arena, size_t size) // size means including a null terminator
{
	size_t	offset;

	if (size > (arena->cap - arena->used))
		return (write(2, "not enough arena space\n", 23), NULL);
	offset = arena->used;
	arena->used += size;
	return (offset);
}
size_t	arena_array_alloc(t_arena *arena, size_t nbr, size_t size) // size means including a null terminator
{
	size_t	offset;

	if (size && nbr > (arena->cap - arena->used) / size)
		return (write(2, "not enough arena space\n", 23), NULL);
	arena_align(arena);
	offset = arena->buf + arena->used;
	arena->used += nbr * size;
	return (offset);
}

void	arena_reset(t_arena *arena)
{
	arena->used = 0;
}
