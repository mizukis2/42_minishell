/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 05:49:12 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/04 01:09:35 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str1, size_t n)
{
	char	*str2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str1[i] && i < n)
		i++;
	str2 = malloc((i + 1) * sizeof(char));
	if (!str2)
		return (NULL);
	while (j < i)
	{
		str2[j] = str1[j];
		j++;
	}
	str2[i] = '\0';
	return (str2);
}
