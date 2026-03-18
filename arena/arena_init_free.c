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
#include "../libft/ft_printf.h"

t_arena	arena_init(size_t size)
{
	t_arena	arena;

	arena = (t_arena){0};
//	errno = 0; // dont't forget about this bad boy
	arena.buf = malloc(size); // if i want to put a zii stub at the beginning, should i add another 8 bytes for it?
	if (!arena.buf)
		handle_exit(EXIT_FAILURE, "arena_init: malloc failed bro\n");
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

void	handle_exit(int status, char *message)
{
	ft_printf(message);
	exit(status);
}
