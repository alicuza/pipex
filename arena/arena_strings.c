/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:05:14 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/18 13:47:18 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

size_t	arena_memcpy(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size);
	ft_memcpy(dest->buf + offset, src, size);
	return (offset);
}

size_t	arena_memset(t_arena *data, int c, size_t size)
{
	size_t	offset;

	offset = arena_alloc(data, size);
	ft_memset(data->buf + offset, c, size);
	return (offset);
}

size_t	arena_strlcpy(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size);
	ft_strlcpy(dest->buf + offset, src, size);
	return (offset);
}

size_t	count_words(const char *s, char del)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != del && (i == 0 || s[i - 1] == del))
			count++;
		i++;
	}
	return (count);
}

size_t	word_len(const char *s, char del)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != del)
		i++;
	return (i);
}

size_t	arena_split(t_arena *dest, const char *src, char del)
{
	size_t	offset;
	size_t	i;
	size_t	word_cnt;
	size_t	len;

	word_cnt = count_words(src, del);
	offset = arena_alloc(dest, (word_cnt + 1) * sizeof(char *));
	i = -1;
	while (++i < word_cnt)
	{
		while (*src == del)
			src++;
		len = word_len(src, del);
		((char **)(dest->buf + offset))[i] = dest->buf + arena_strlcpy(dest, src, (len + 1) * sizeof(char));
		src += len + 1;
	}
	((char **)(dest->buf + offset))[i] = dest->buf + arena_memset(dest, 0, sizeof(NULL)); // NULL ptr as terminator
	return (offset);
}


