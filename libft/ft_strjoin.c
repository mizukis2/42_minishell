/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:31:23 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/25 04:13:41 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length;
	char	*newstr;
	int		i;
	int		j;

	length = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	newstr = malloc((length + 1) * sizeof(char));
	if (!newstr)
	{
		return (NULL);
	}
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		newstr[j + i] = s2[j];
		j++;
	}
	newstr[j + i] = '\0';
	return (newstr);
}
