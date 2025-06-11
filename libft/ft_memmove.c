/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:46:45 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/26 19:29:57 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*chardest;
	char	*charsrc;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	chardest = (char *) dest;
	charsrc = (char *) src;
	if (chardest > charsrc)
	{
		while (len > 0)
		{
			chardest[len - 1] = charsrc[len - 1];
			len--;
		}
	}
	i = 0;
	while (i < len)
	{
		chardest[i] = charsrc[i];
		i++;
	}
	return (dest);
}
