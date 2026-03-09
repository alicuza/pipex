/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:13:29 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 13:21:01 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str	ft_substr(t_arena *arena, t_str *s, unsigned int start, size_t len)
{
	t_str	sub;

	sub = (t_str){0};
	if (!s)
		return (sub);
	if (len < (size_t)start)
		return (sub);
	else
		sub.len = s->len - (size_t)start;
	if (sub.len > len)
		sub.len = len;
	sub.data = arena_alloc(arena, sub.len + 1, 1);
	if (!sub.data)
		return (sub);
	ft_strlcpy(sub.data, s->data + start, sub.len + 1);
	return (sub);
}
