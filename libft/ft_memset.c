/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:41:45 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/25 04:10:50 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t n)
{
	unsigned char	*ptr;
	size_t			a;

	ptr = (unsigned char *)str;
	a = 0;
	while (a < n)
	{
		ptr[a] = (unsigned char)value;
		a++;
	}
	return (str);
}
