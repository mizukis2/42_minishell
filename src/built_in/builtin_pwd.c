/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                       :+:    :+:           */
/*                                                     +:+                    */
/*   By: mmatsui <mmatsui@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/27 11:58:09 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/07/10 16:48:37 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	*cwd;

	if (count_args(args) > 2)
		return (print_error_builtin("cd: too many arguments\n"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("pwd"), 1);
	ft_putstr(cwd);
	write (STDOUT_FILENO, "\n", 1);
	free (cwd);
	return (0);
}
