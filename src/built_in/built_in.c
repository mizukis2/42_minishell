/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   built_in.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 17:07:20 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/19 17:07:21 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(char **args, char **envp)
{
	if(!args || !*args)
		return ;
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args + 1);
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args + 1, envp);
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(args + 1);
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(args + 1);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args + 1);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args + 1);
	if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args + 1);
}

/* test for buildin */
/* int	main (int ac, char **av, char **envp)
{
	char **copied_envp;
	char *cmd;

	copied_envp = env_dup(envp);
	cmd = av[1];
	if (av[1])
		execute_buildin(av, copied_envp);
	return (0);
} */