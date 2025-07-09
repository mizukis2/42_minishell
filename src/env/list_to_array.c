/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   list_to_array.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/09 09:01:26 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/09 09:01:28 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_nodes(t_env *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->exported)
			count++;
		head = head->next;
	}
	return (count);
}

static char	*complete_env_line(t_env *envp)
{
	char	*env_line;
	char	*temp;
	temp = ft_strjoin(envp->key, "=");
	if (!temp)
		return (NULL);
	env_line = ft_strjoin(temp, envp->value);
	if (!env_line)
	{
		free (temp);
		return (NULL);
	}
	free (temp);
	return (env_line);
}

/* this function convert the envp (linked list) to the envp (char **)
for the usage of execv. This array doesn't contain the unexported one
(export KEY : without = and value) */
char	**list_to_array(t_env *envp)
{
	char	**array_envp;
	t_env *curr;
	int	i;
	int	count;

	count = count_nodes(envp);
	array_envp = malloc (sizeof(char *) * (count + 1));
	if (array_envp)
		return (NULL);
	curr = envp;
	i = 0;
	while (curr)
	{
		if (curr->exported)
		{
			array_envp[i] = complete_env_line(curr);
			if (!(array_envp[i]))
			{
				free_array(array_envp);
				return (NULL);
			}
			i++;
		}
		curr = curr->next;
	}
	array_envp[i] = NULL;
	return (array_envp);
}

