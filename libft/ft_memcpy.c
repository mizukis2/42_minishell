/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:39:02 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/26 18:39:24 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destchar;
	char	*srcchar;
	size_t	i;

	if (!dest && !src)
	{
		return (NULL);
	}
	destchar = (char *) dest;
	srcchar = (char *) src;
	i = 0;
	while (i < n)
	{
		destchar[i] = srcchar[i];
		i++;
	}
	return (dest);
}
