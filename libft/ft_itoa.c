/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:53:03 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/25 04:09:36 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
	{
		return (1);
	}
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static char	*makestring(int len)
{
	char	*string;

	string = malloc(sizeof(char) * (len + 1));
	return (string);
}

char	*ft_itoa(int nbr)
{
	int		len;
	char	*result;
	int		i;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	len = int_len(nbr);
	i = len - 1;
	result = makestring(len);
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	else if (nbr == 0)
		result[0] = '0';
	while (nbr != 0)
	{
		result[i--] = ((nbr % 10) + '0');
		nbr = nbr / 10;
	}
	result[len] = '\0';
	return (result);
}
