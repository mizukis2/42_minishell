/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:34:07 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/25 04:14:25 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = 0;
	srclen = 0;
	i = 0;
	while (dest[destlen] && destlen < destsize)
		destlen++;
	while (src[srclen])
		srclen++;
	if (destlen == destsize)
		return (destlen + srclen);
	while (src [i] && i < destsize - destlen - 1)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
