/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_exit.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/09 14:46:39 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/09 14:46:40 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//#include "builtin.h"

static void	print_error_exit(char *arg)
{
	print_error ("exit: ");
	print_error (arg);
	print_error (": numeric argument required\n");
}

void	clean_all(t_shell *shell)
{
	free(shell->line);
	free_node_list(shell->envp);
	free_cmd_list(shell->commands);
	cleanup(shell->tokens, shell->line);
	free (shell);
	rl_clear_history();
}

static bool	is_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;	
	}
	return (true);
}

static int	convert_exit_code(char *arg)
{
	int	code;

	code = ft_atoi(arg);
	if (code > 255)
		code = code % 256;
	return (code);
}

int	ft_exit(t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr ("exit\n");
	if (shell->commands->argv[0] && !(is_numeric(shell->commands->argv[0])))
	{
		print_error_exit(shell->commands->argv[0]);
		clean_all(shell);
		return (2); //this should update later
	}
	if (shell->commands->argv[0] && shell->commands->argv[1])
		return (print_error("exit: too many arguments\n"), 1);
	//if there is no argument, then return with last_exit_code
	if (shell->commands->argv[0] && (is_numeric(shell->commands->argv[0])))
		exit_code = convert_exit_code(shell->commands->argv[0]);
	clean_all(shell);
	printf ("exit code(cmd:exit): %d\n",exit_code);
	exit (exit_code);
}
