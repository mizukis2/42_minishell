/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   update_env.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/04 12:36:39 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/04 12:36:45 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static function for update_env functon */
static void	update_value(t_env *node, const char *new_value)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;
}

/* static function for update_env functon */
static char	*create_env_str(const char *key, const char *path)
{
	char	*env_str;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	if (path)
		env_str = ft_strjoin(temp, path);
	else
		env_str = temp;
	free (temp);
	return (env_str);
}

/* static function for update_env functon */
static int	update_existing_env(t_env *curr, const char *key, const char *path)
{
	if (ft_strcmp(curr->key, key) == 0)
	{
		if (path != NULL)
			curr->exported = true;
		update_value(curr, path);
		return (1);
	}
	return (0);
}

/* update the environmental variable (linked list) by 
updating the path or adding the new node */
void	update_env(const char *key, const char *path, t_env *envp)
{
	t_env	*curr;
	char	*env_line;
	t_env	*new;

	curr = envp;
	while (curr)
	{
		if (update_existing_env(curr, key, path))
			return ;
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	if (path)
		env_line = create_env_str(key, path);
	else
		env_line = ft_strdup(key);
	if (!env_line)
		return ;
	new = create_node(env_line);
	free (env_line);
	if (new)
		curr->next = new;
}
