/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/22 11:55:46 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "arena.h"
#include <errno.h>
#include <string.h>

/*
 * natural alignment of 64bit systems is 8
 */

static void	arena_align(t_arena *arena, size_t align)
{
	arena->used = (arena->used + (align - 1)) & ~(align - 1);
}

size_t	arena_alloc(t_arena *arena, size_t size, size_t align)
{
	size_t	offset;

	arena_align(arena, align);
	if (size > (arena->cap - arena->used))
	{
		if (arena->clean)
			arena->clean(arena->env);
		handle_exit_msg("arena", "alloc", strerror(ENOMEM), 1);
		exit(1);
	}
	offset = arena->used;
	arena->used += size;
	return (offset);
}

void	arena_reset(t_arena *arena)
{
	arena->used = 0;
}
