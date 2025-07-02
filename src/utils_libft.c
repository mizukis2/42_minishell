/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_libft.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/19 17:54:08 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/30 14:02:36 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

/* The strcmp() function compares the two strings s1 and s2.
0, if the s1 and s2 are equal; */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/* It searches for the first occurrence of a character in a string
Input: a string s, and a character c to search for
Output: pointer to the first occurrence of c in s — or NULL if not found */
char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while(haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
