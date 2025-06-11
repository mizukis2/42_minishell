/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 05:06:08 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/25 04:13:15 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	char	*str2;
	size_t	len;
	size_t	i;

	len = ft_strlen(str1);
	i = 0;
	str2 = malloc((len + 1) * sizeof(char));
	if (str2 == NULL)
	{
		return (NULL);
	}
	while (str1[i])
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
