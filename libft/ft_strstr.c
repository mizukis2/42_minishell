/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strstr.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/04 08:25:54 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/04 08:25:56 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

