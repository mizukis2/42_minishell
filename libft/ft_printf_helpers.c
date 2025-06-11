/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:37:37 by zekhatib          #+#    #+#             */
/*   Updated: 2025/02/15 04:45:11 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_string(char *s, int ccount)
{
	if (!s)
		return (print_string("(null)", ccount));
	while (*s)
	{
		ccount = print_char(*s, ccount);
		if (ccount == -1)
			return (-1);
		s++;
	}
	return (ccount);
}

int	convert_hex(unsigned long num, int ccount, char c)
{
	if (num == 0)
		ccount = print_char('0', ccount);
	else if (num >= 16)
	{
		ccount = convert_hex(num / 16, ccount, c);
		if (ccount == -1)
			return (-1);
		ccount = convert_hex(num % 16, ccount, c);
		if (ccount == -1)
			return (-1);
	}
	else if (num <= 9)
		ccount = print_char(num + '0', ccount);
	else
	{
		if (c == 'x')
			ccount = print_char((num + 'a') - 10, ccount);
		else if (c == 'X')
			ccount = print_char((num + 'A') - 10, ccount);
	}
	return (ccount);
}

int	print_pointer(va_list args, int ccount)
{
	void		*ptr;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (print_string("(nil)", ccount));
	ccount = print_string("0x", ccount);
	if (ccount == -1)
		return (-1);
	return (convert_hex((unsigned long)ptr, ccount, 'x'));
}

int	print_integer(int num, int ccount)
{
	if (num == -2147483648)
		return (print_string("-2147483648", ccount));
	if (num < 0)
	{
		ccount = print_char('-', ccount);
		if (ccount == -1)
			return (-1);
		num = -num;
	}
	if (num > 9)
	{
		ccount = print_integer(num / 10, ccount);
		if (ccount == -1)
			return (-1);
	}
	return (print_char((num % 10) + '0', ccount));
}

int	print_unsigned_dec(unsigned int unum, int ccount)
{
	if (unum > 9)
	{
		ccount = print_unsigned_dec(unum / 10, ccount);
		if (ccount == -1)
			return (-1);
	}
	return (print_char((unum % 10) + '0', ccount));
}
