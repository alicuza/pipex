/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:41:35 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/16 15:14:01 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H
# include <stdlib.h>
# define ALIGNMENT 8

typedef struct s_arena
{
	char	*buf;
	size_t	used;
	size_t	cap;
}	t_arena;

//typedef (void)(*t_handle_exit_fn)(void *, int, const char *); // probably not necessary

t_arena	arena_init(void *env, size_t cap);
size_t	arena_alloc(void *env, t_arena *arena, size_t size);
size_t	arena_array_alloc(void *env, t_arena *arena, size_t nbr, size_t size);
void	arena_clear(t_arena *arena);
size_t	arena_memcpy(t_arena *dest, const void *src, size_t size);
size_t	arena_strlcpy(t_arena *dest, const void *src, size_t size);
size_t	arena_memset(t_arena *data, int c, size_t size);
size_t	arena_split(t_arena *dest, const char *src, char del);
size_t	arena_save(t_arena *arena);
void	arena_restore(t_arena *arena, size_t idx);
void	arena_free(t_arena *arena);

#endif
