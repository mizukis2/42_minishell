/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_unset.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/09 10:10:55 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/09 10:10:57 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "builtin.h"

static void	delete_node(t_env *delete, t_env *prev)
{
	if (delete)
	{
		prev->next = delete->next;
		free_node(delete);
		return ;
	}
}

static void	check_delete_env(char *arg, t_env *curr, t_env *prev, t_env **envp)
{
	while (curr)
	{
		if (ft_strcmp(arg, curr->key) == 0)
		{
			if (prev == NULL)
			{
				*envp = curr->next;
				free_node (curr);
				return ;
			}
			else
				delete_node(curr, prev);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	return ;
}

int	ft_unset(char **args, t_env **envp)
{
	t_env	*curr;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[i])
	{
		curr = *envp;
		prev = NULL;
		check_delete_env(args[i], curr, prev, envp);
		i++;
	}
	return (0);
}
