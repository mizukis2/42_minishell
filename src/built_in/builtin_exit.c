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

//#include "minishell.h"

#include "builtin.h"

static void	print_error_exit(char *arg)
{
	print_error ("exit: ");
	print_error (arg);
	print_error (": numeric argument required\n");
}

static void	cleanup_exit(t_env *envp) //need to update later
{
	free_node_list(envp);
	//free_node_list(parcing linked list)
	//free history
	//free other struct
	rl_clear_history();
}

static bool is_numeric(char *arg)
{
	int i;

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

int	ft_exit(char **args, t_env **envp) //these parameter need to update later
{
	(void)envp;//dummy
	int exit_code;

	ft_putstr ("exit\n");
	if (args[0] && !(is_numeric(args[0])))
	{
		print_error_exit(args[0]);
		cleanup_exit(*envp);
		return (255); //exit (255); this should update later
	}
	if (args[1])
		return (print_error("exit: too many arguments\n"), 1);
	if (args[0] != NULL)
		exit_code = convert_exit_code(args[0]);
	else 
		exit_code = 0;
	cleanup_exit(*envp); //this parameters need to change after execution part completed
	//exit (exit_code); 
	printf ("exit code:%d\n",exit_code);
	return (-42); //this is just dummy return
}

