/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:05:14 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/15 23:18:17 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

size_t	arena_memcpy(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size);
	ft_memcpy(&dest[offset], src, size);
	return (offset);
}

static size_t	count_words(const char *s, char del)
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

static size_t	word_len(const char *s, char del)
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
	offset = arena_alloc(dest, word_cnt * sizeof(size_t));
	i = -1;
	while (++i < word_cnt)
	{
		while (*src == del)
			src++;
		len = word_len(src, del);
		((int *)(dest->buf))[i] = arena_memcpy(dest, len * sizeof(char));
		dest->used++; // adding a null terminator to the end;
		src += len + 1;
	}
	// think about whether you want to have a stub at the beginning, or if that will just be annoying, since they need to be contiguous to be passed to execve as its argument string array
}

