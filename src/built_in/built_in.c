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
		return (1);
}

int	execute_builtin_exit(t_shell *shell, int save_in, int save_out)
{
	return (ft_exit(shell, save_in, save_out));
}



//the number should be exit code here



/* test for buildin */

/* void	enter_shell_loop(char **envp)
{
	char	*line;
	char	**args;
	t_env	*env_list;
	int		result;
	
	env_list = copy_initial_env(envp);
	if (!env_list)
		return (perror("copy_initial_env failed"));
	while (1)
	{
		line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (!line) // check for EOF Ctrl+D (temporary)
			break ;
		add_history(line);
		args = ft_split(line, ' ');
		if (!args)
		{
			free(line);
			continue ;
		}
		result = execute_builtin(args, env_list);
		printf ("result from command:%d\n", result);
		free_array(args);
		free (line);
	}
	free_node_list(env_list);
}

static int	args_check(int ac, char **envp)
{
	if (ac != 1 || !envp || !*envp || !**envp)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;

	if (!args_check(ac, envp))
		return (EXIT_FAILURE);
	enter_shell_loop(envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
} */