/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   env_utils.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/04 12:36:39 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/04 12:36:45 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *node)
{
	if (!node)
		return;
	if(node->key)
		free(node->key);
	if(node->value)
		free(node->value);
	free(node);
}

void	free_node_list(t_env *head)
{
	t_env *temp;
	while(head)
	{
		temp = head->next;
		free_node(head);
		head = temp;
	}
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

int	count_nodes(t_env *head)
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

char	*complete_env_line(t_env *envp)
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
char **list_to_array(t_env *envp)
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

/* static function for update_env functon */
static void	update_value(t_env *node, const char *new_value)
{
	if (!node)
		return;
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_value);
}

/* static function for update_env functon */
static char	*create_env_str(const char *key, const char *path)
{
	char	*env_str;
	char	*temp;
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	env_str = ft_strjoin(temp, path);
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
			return (update_value(curr, path));
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	env_line = create_env_str(key, path);
	if (!env_line)
		return ;
	new = create_node(env_line);
	free (env_line);
	if (!new)
		return ;
	curr->next = new;
}
