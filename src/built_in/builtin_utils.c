/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <mmatsui@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 10:37:54 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/27 16:09:28 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "builtin.h"

/* Count the number of arguments in a null-terminated array */
int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

char	*get_env_value(t_env *envp, char *key)
{
	t_env *curr;

	curr = envp;
	while (curr)
	{
		if(ft_strcmp(curr->key, key) == 0)
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (NULL);
}

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}