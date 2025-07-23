/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   env_utils.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/09 08:58:32 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/09 08:58:34 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free (node->key);
	if (node->value)
		free (node->value);
	free (node);
}

void	free_node_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head->next;
		free_node(head);
		head = temp;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}
