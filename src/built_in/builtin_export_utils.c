/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_export_utils.c                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/11 13:14:44 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/11 13:14:45 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_list(t_env **arr, size_t n)
{
	size_t	pass;
	size_t	j;
	t_env	*temp;

	if (n < 2)
		return ;
	pass = 0;
	while (pass < n - 1)
	{
		j = 0;
		while (j < n - pass -1)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		pass++;
	}
}

static void	print_list(t_env **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		write (STDOUT_FILENO, "declare -x ", 11);
		ft_putstr(arr[i]->key);
		if (arr[i]->exported && arr[i]->value)
		{
			write (STDOUT_FILENO, "=\"", 2);
			ft_putstr(arr[i]->value);
			write (STDOUT_FILENO, "\"", 1);
		}
		write (STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	print_all_list(t_env *env_list)
{
	size_t	n;
	t_env	**arr;
	t_env	*curr;
	size_t	i;

	n = count_nodes(env_list);
	if (n == 0)
		return ;
	arr = malloc (n * sizeof(*arr));
	if (!arr)
		return ;
	i = 0;
	curr = env_list;
	while (i < n)
	{
		arr[i] = curr;
		i++;
		curr = curr->next;
	}
	sort_list(arr, n);
	print_list(arr, n);
	free (arr);
}
