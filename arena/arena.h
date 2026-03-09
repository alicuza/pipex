/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:41:35 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 09:57:41 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H
# include <stdlib.h>

typedef struct s_arena
{
	char	*buf;
	size_t	used;
	size_t	cap;
}	t_arena;

t_arena	arena_init(size_t nbr, size_t size);
void	*arena_alloc(t_arena *arena, size_t nbr, size_t size);
void	arena_reset(t_arena *arena);
size_t	arena_save(t_arena *arena);
void	arena_restore(t_arena *arena, size_t saved_idx);
void	arena_free(t_arena *arena);

#endif


