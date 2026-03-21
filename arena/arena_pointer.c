/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 20:27:55 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*get_arena_ptr(t_arena *arena, size_t idx)
{
	return (arena->buf + idx);
}
