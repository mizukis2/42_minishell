/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   copy_initial_env.c                                  :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 14:50:19 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 14:50:21 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_key_value(t_env *node, char *str, int len)
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

static int	set_key(t_env *node, char *str)
{
	node->key = ft_strdup(str);
	if (!(node->key))
	{
		free_node(node);
		return (1);
	}
	return (0);
}

static t_env *create_node(char *str)
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

/* copy the environmental variable from main (char **envp) 
as linked list */
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
/* int main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;

	t_env	*env_list;
	t_env	*curr;

	env_list = copy_initial_env(envp);
	curr = env_list;
	while (curr)
	{
		if (curr->exported && curr->value)
		{
			printf ("%s=%s\n", curr->key, curr->value);
			curr = curr->next;
		}
	}

	free_node_list(env_list);
	return (EXIT_SUCCESS);
} */