/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_save_restore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:36:13 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 09:54:40 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

size_t	arena_save(t_arena *arena)
{
	return (arena->used);
}

void	arena_restore(t_arena *arena, size_t idx)
{
	arena->used = idx;
}
