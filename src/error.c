/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   error.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 13:14:32 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 13:14:34 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* print error messafe as "Stundard error" */
void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
