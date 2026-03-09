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

void	*arena_alloc(t_arena *arena, size_t nbr, size_t size)
{
	char	*pos;

	if (size && nbr > (arena->cap - arena->used) / size)
		return (write(2, "not enough arena space\n", 23), NULL);
	pos = arena->buf + arena->used;
	arena->used += nbr * size;
	arena->used = (arena->used + 7) & ~7;
	return ((void *)pos);
}

void	arena_reset(t_arena *arena)
{
	arena->used = 0;
}
