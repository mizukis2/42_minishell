/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:55:59 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/26 20:28:31 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int	words;
	int	inword;

	words = 0;
	inword = 0;
	while (*s)
	{
		if (*s != c && !inword)
		{
			words++;
			inword = 1;
		}
		else if (*s == c && inword)
		{
			inword = 0;
		}
		s++;
	}
	return (words);
}

static	char	*copyarr(char const *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
	{
		len++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		return (NULL);
	}
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**freeall(char **result, int i)
{
	while (i > 0)
	{
		free (result[i - 1]);
		i--;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = copyarr(s, c);
			if (!result[i])
				return (freeall(result, i));
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
