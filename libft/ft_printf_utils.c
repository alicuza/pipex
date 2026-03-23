/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:38:01 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/23 15:10:47 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_nbr(const char **s)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret *= 10;
		ret += **s - 48;
		(*s)++;
	}
	return (ret);
}

int	ft_abs_nbr_len(unsigned long n, unsigned long base)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

int	*allowed_flags(void)
{
	static int	ret[9];

	ret[0] = FLAG_MINUS;
	ret[1] = FLAG_MINUS | FLAG_DOT;
	ret[3] = FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT;
	ret[4] = FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT;
	ret[5] = FLAG_MINUS | FLAG_ZERO | FLAG_DOT;
	ret[6] = FLAG_MINUS;
	ret[7] = FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT;
	ret[8] = FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT;
	return (ret);
}
