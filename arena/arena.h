/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:41:35 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/20 11:12:49 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_arena
{
	char	*buf;
	size_t	used;
	size_t	cap;
	void	(*clean)(void *);
	void	*env;
}	t_arena;

t_arena	arena_init(size_t cap);
size_t	arena_alloc(t_arena *arena, size_t size, size_t align);
void	arena_clear(t_arena *arena);
size_t	arena_memset(t_arena *data, int c, size_t size, size_t align);
size_t	arena_memcpy(t_arena *dest, const void *src, size_t size, size_t align);
size_t	arena_strlcpy(t_arena *dest, const void *src, size_t size);
size_t	arena_split(t_arena *dest, const char *src, char del);
size_t	arena_save(t_arena *arena);
void	arena_restore(t_arena *arena, size_t idx);
void	arena_hook_cleanup(t_arena *arena, void (*clean)(void *), void *env);
void	arena_free(t_arena *arena);
void	*get_arena_ptr(t_arena *arena, size_t idx);
#endif
