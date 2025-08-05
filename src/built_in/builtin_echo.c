/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <mmatsui@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 14:48:36 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/30 12:19:49 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_all_n_flags(char *arg)
{
	int	j;

	j = 2;
	while (arg[j] == 'n')
		j++;
	if (arg[j])
		return (false);
	return (true);
}

int	ft_echo(char **args)
{
	bool	no_line;
	int		i;

	printf ("enter echo\n");
	i = 0;
	no_line = false;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		if (!is_all_n_flags(args[i]))
			break ;
		no_line = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			write (STDOUT_FILENO, " ", 1);
		i++;
	}
	printf ("finish putstr\n");
	if (!no_line)
		write (STDOUT_FILENO, "\n", 1);
	return (0);
}
