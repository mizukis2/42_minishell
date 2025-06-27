/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 14:48:36 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/27 16:01:38 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	bool	no_line;
	int		i;
	int		j;

	i = 0;
	no_line = false;
	while(args[i] && args[i][0] == '-' && args[i][1] =='n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		no_line = true;
		i++;
	}
	while(args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (!no_line)
		write (1, "\n", 1);
	return (0);
}


