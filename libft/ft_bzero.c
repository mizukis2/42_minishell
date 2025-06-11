/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:56:46 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/25 04:07:24 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			a;
	unsigned char	*ptr;

	ptr = (unsigned char *) str;
	a = 0;
	while (a < n)
	{
		ptr[a] = 0;
		a++;
	}
}
