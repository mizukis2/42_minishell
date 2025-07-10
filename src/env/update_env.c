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
/* this used for mainly export function. */
char	*create_new_key(const char *arg)
{
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len));
}

/* this used for mainly export function. */
char	*create_new_value(const char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (!arg[len])
		return (NULL);
	return (ft_strdup(arg + len + 1));
}

/* static function for update_env functon */
static void	update_value(t_env *node, const char *new_value)
{
	if (!node)
		return;
	if (node->value)
		free(node->value);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;  //changed
}

/* static function for update_env functon */
static char	*create_env_str(const char *key, const char *path)
{
	char	*env_str;
	char	*temp;
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	if (path) //changed
		env_str = ft_strjoin(temp, path);
	else
		env_str = temp;
	free (temp);
	return (env_str);
}

/* update the environmental variable (linked list) by 
updating the path or adding the new node */
void	update_env(const char *key, const char *path, t_env *envp)
{
	t_env *curr;
	char *env_line;
	t_env *new;

	curr = envp;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (path != NULL)
				curr->exported = true;
			return (update_value(curr, path));
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	if (path)
		env_line = create_env_str(key, path); //changed around here
	else
		env_line = ft_strdup(key);
	if (!env_line)
		return ;
	new = create_node(env_line);
	free (env_line);
	if (!new)
		return ;
	curr->next = new;
}
