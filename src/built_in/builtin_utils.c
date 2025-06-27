/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_utils.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/25 10:37:54 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/25 10:37:55 by mmatsui        ########   odam.nl        */
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

