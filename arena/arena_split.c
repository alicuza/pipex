/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:26:16 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 20:52:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

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
	offset = arena_alloc(dest, (word_cnt + 1) * sizeof(char *),
			_Alignof(char *));
	i = 0;
	while (i < word_cnt)
	{
		while (*src == del)
			src++;
		len = word_len(src, del);
		((char **)(dest->buf + offset))[i]
			= dest->buf + arena_strlcpy(dest, src, (len + 1) * sizeof(char));
		src += len;
		i++;
	}
	((char **)(dest->buf + offset))[i] = NULL;
	return (offset);
}
