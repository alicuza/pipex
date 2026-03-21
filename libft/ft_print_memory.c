/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:21:53 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/17 11:46:59 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	dec_to_hex_n(char *hex, unsigned long dec, int length)
{
	char	*hex_table;

	hex_table = "0123456789abcdef";
	while (length > 0)
	{
		hex[length - 1] = hex_table[dec % 16];
		dec = dec / 16;
		length--;
	}
}

static void	print_hex_addr(void *addr)
{
	char	buffer[16];
	int		counter;

	counter = 0;
	while (counter < 16)
	{
		buffer[counter] = '0';
		counter++;
	}
	dec_to_hex_n(buffer, (unsigned long) addr, 16);
	write(1, buffer, 16);
	write(1, ": ", 2);
}

static void	print_hex_string(void *addr, unsigned int size)
{
	int		counter;
	int		index;
	char	buffer[40];
	char	*value;

	value = (char *)addr;
	counter = 0;
	index = 0;
	while (index < 16)
	{
		if (index < (int)size)
		{
			dec_to_hex_n(&buffer[counter], value[index], 2);
			index++;
			counter += 2;
		}
		else
			buffer[counter++] = ' ';
		if (index % 2 == 0)
			buffer[counter++] = ' ';
	}
	write(1, buffer, 40);
}

static void	print_char_dot(void *addr, unsigned int size)
{
	int		counter;
	char	*value;

	value = (char *)addr;
	counter = 0;
	while (counter < 16)
	{
		if (counter < (int)size)
		{
			if (value[counter] < 32 || value[counter] > 126)
				write(1, ".", 1);
			else
				write(1, value + counter, 1);
		}
		counter++;
	}
}

void	*ft_print_memory(void *addr, size_t size)
{
	int	lines;
	int	counter;

	lines = (size + 15) / 16;
	if (!size)
		return (NULL);
	counter = 0;
	while (counter < lines - 1)
	{
		print_hex_addr(addr + counter * 16);
		print_hex_string(addr + counter * 16, size - counter * 16);
		print_char_dot(addr + counter * 16, size - counter * 16);
		write(1, "\n", 1);
		counter++;
	}
	print_hex_addr(addr + counter * 16);
	print_hex_string(addr + counter * 16, size - counter * 16);
	print_char_dot(addr + counter * 16, size - counter * 16);
	write(1, "\n", 1);
	return (addr);
}

/*
int main(void)
{
	ft_print_memory("Bonjour les aminpeut faire avec", 40);
	return (0);
}
*/
