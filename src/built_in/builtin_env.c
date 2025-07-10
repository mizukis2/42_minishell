/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <mmatsui@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 16:26:56 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/30 15:34:09 by mmatsui       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "builtin.h"

int	ft_env(char **args, t_env *envp)
{
	char	*env_str;
	t_env	*curr;

	curr = envp;
	if (count_args(args) > 1)
		return (print_error("env: too many arguments\n"), 1);
	while (curr)
	{
		if ((curr->exported && curr->value))
		{
			env_str = complete_env_line(curr);
			if (!env_str)
				return (print_error("env: memory allocation failed\n"), 1);
			ft_putstr(env_str);
			write (STDOUT_FILENO, "\n", 1);
			free (env_str);
		}
		curr = curr->next;
	}
	return (0);
}
