/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exec_path.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/27 17:16:35 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/27 17:16:36 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*complete_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	full = ft_strjoin(temp, cmd);
	free (temp);
	return (full);
}

static char	**prep_all_path(t_env *envp)
{
	t_env	*curr;

	curr = envp;
	while (curr && ft_strcmp(curr->key, "PATH") != 0)
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (ft_split(curr->value, ':'));
}

char	*find_path(char *cmd, t_env *envp)
{
	int		i;
	char	**all_path;
	char	*full;

	all_path = prep_all_path(envp);
	if (!all_path)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		full = complete_path(all_path[i], cmd);
		if (access(full, X_OK) == 0)
			return (free_split(all_path), full);
		free (full);
		i++;
	}
	free_split(all_path);
	return (NULL);
}
