/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strcmp.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/04 08:24:13 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/04 08:24:15 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
