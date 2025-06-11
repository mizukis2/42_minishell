/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:20:17 by zekhatib          #+#    #+#             */
/*   Updated: 2025/02/15 04:43:58 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(char c, int ccount)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (ccount + 1);
}

int	printspecifier(const char *format, va_list args, int pos, int ccount)
{
	if (format[pos] == 'c')
		ccount = print_char(va_arg(args, int), ccount);
	else if (format[pos] == 's')
		ccount = print_string(va_arg(args, char *), ccount);
	else if (format[pos] == 'p')
		ccount = print_pointer(args, ccount);
	else if (format[pos] == 'd' || format[pos] == 'i')
		ccount = print_integer(va_arg(args, int), ccount);
	else if (format[pos] == 'u')
		ccount = print_unsigned_dec(va_arg(args, unsigned int), ccount);
	else if (format[pos] == 'x' || format[pos] == 'X')
		ccount = convert_hex((unsigned long)va_arg(args, unsigned int), \
		ccount, format[pos]);
	else if (format[pos] == '%')
		ccount = print_char('%', ccount);
	else
	{
		ccount = print_char('%', ccount);
		if (ccount == -1)
			return (-1);
		ccount = print_char(format[pos], ccount);
	}
	return (ccount);
}

int	ft_printf(const char *format, ...)
{
	int		ccount;
	int		pos;
	va_list	args;

	ccount = 0;
	pos = 0;
	va_start(args, format);
	while (format[pos])
	{
		if (format[pos] == '%')
		{
			pos++;
			ccount = printspecifier(format, args, pos, ccount);
			if (ccount == -1)
				return (va_end(args), -1);
		}
		else
		{
			ccount = print_char(format[pos], ccount);
			if (ccount == -1)
				return (va_end(args), -1);
		}
		pos++;
	}
	return (va_end(args), ccount);
}
