/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   env_dup.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 14:50:19 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 14:50:21 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
	{
		l++;
	}
	return (l);
}

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

void	free_array (char **array)
{
	int	i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}
 */
char **env_dup(char **envp)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			free_array(copy);
			return(NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
/* 
int	main (int ac, char **av, char **envp)
{
	char **copy;
	int	i = 0;
	if (ac != 1)
		return (1);
	if (!av || !*av || !**av || !envp || !*envp|| !**envp)
		return (1);
	
	copy = env_dup(envp);
	while (copy[i])
	{
		printf("%s\n", copy[i]);
		i++;
	}
	free_array(copy);
	return (0);
}
 */