/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:58:40 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 12:30:57 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str *ft_strjoin(t_arena *arena, t_str *s1, t_str *s2)
{
	t_str	*res;
	size_t	total_size;

	if (!s1 || !s2)
		return (NULL);
	total_size = s1->used + s2->used + 1;
	res = arena_alloc(total_size + sizeof(size_t));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1->data, total_size);
	ft_strlcat(res, s2->data, total_size);
	return (res);
}
