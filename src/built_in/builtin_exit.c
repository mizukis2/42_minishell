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

static void	print_error_numeric(char *arg)
{
	print_error_builtin ("exit: ");
	print_error_builtin (arg);
	print_error_builtin (": numeric argument required\n");
}

void	clean_all(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->env_list)
		free_node_list(shell->env_list);
	if (shell->commands)
		free_cmd_list(shell->commands);
	if (shell->tokens)
		free_tokens(shell->tokens);
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

/* this runs in parent, clean all when run "exit" here */
int	ft_exit(t_shell *shell, int save_in, int save_out)
{
	int	exit_code;

	exit_code = shell->last_exit_code;
	ft_putstr ("exit\n");
	if (shell->commands->argv[1] && !(is_numeric(shell->commands->argv[1])))
	{
		print_error_numeric(shell->commands->argv[1]);
		restore_std_close_fd(save_in, save_out);
		clean_all(shell);
		exit (2);
	}
	if (shell->commands->argv[1] && shell->commands->argv[2])
	{
		restore_std_close_fd(save_in, save_out);
		return (print_error_builtin("exit: too many arguments\n"), 1);
	}
	if (shell->commands->argv[1])
		exit_code = convert_exit_code(shell->commands->argv[1]);
	restore_std_close_fd(save_in, save_out);
	clean_all(shell);
	exit (exit_code);
}
