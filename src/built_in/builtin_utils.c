/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 10:37:54 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/27 16:09:28 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Count the number of arguments in a null-terminated array */
int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
