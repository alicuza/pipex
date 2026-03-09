/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:49:45 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 09:40:35 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str	*ft_strdup(t_arena *arena, t_str s)
{
	t_str	dst;

	dst = (t_str)(arena->buf + arena->used);
	arena->used += sizeof(t_str);
	ft_strlcpy(dst.data, s.data, s.cap);
	return (dst);
}
