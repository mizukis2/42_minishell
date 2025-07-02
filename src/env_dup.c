/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   env_dup.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <@student.codam.nl>                   +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 14:50:19 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 14:50:21 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	free_array (char **array)
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
/* copy environment variable from char **envp in main*/
/* char **env_dup(char **envp)
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
 */

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

int	set_key_value(t_env *node, char *str, int len)
{
	node->key = ft_substr(str, 0, len);
	if (!(node->key))
	{
		free_node(node);
		return (1);
	}
	node->value = ft_strdup(str + len + 1);
	if (!(node->value))
	{
		free_node(node);
		return (1);
	}
	return (0);
}

int	set_key(t_env *node, char *str)
{
	node->key = ft_strdup(str);
	if (!(node->key))
	{
		free_node(node);
		return (1);
	}
	return (0);
}

t_env *create_node(char *str)
{
	char	*eq;
	int		key_len;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		key_len = eq - str;
		if (set_key_value(new, str, key_len))
			return (NULL);
	}
	else
	{
		if (set_key(new, str))
			return (NULL);
		new->value = NULL;
	}
	new->exported = true;
	new->next = NULL;
	return (new);
}

t_env	*copy_initial_env(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_node(envp[i]);
		if (!new_node)
		{
			free_node_list(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
}
