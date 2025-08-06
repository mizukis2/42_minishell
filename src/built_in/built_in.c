/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   built_in.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 17:07:20 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/19 17:07:21 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args, t_env *envp)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args + 1));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args + 1, envp));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args + 1));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args + 1, envp));
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args + 1, envp));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args + 1, &envp));
	else
		return (print_error_builtin("minishell: out of builtin"), 1);
}

int	execute_builtin_exit(t_shell *shell, int save_in, int save_out)
{
	return (ft_exit(shell, save_in, save_out));
}
