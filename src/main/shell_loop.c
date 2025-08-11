/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 08:18:01 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->last_exit_code = 0;
	shell->env_list = copy_initial_env(envp);
	if (!shell->env_list)
	{
		print_error("ERROR - Unable to make list of Environment Variables");
		shell->last_exit_code = 1;
		return (0);
	}
	return (1);
}

void	clean_shell(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->commands)
		free_cmd_list(shell->commands);
	if (shell->tokens)
		free_tokens(shell->tokens);
}

static void	free_env(t_env *head)
{
	return (free_node_list(head));
}

void	start_shell(char **envp)
{
	t_shell	shell;

	if (!init_shell(&shell, envp))
		return ;
	while (1)
	{
		shell.line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (!shell.line) // check for EOF Ctrl+D (temporary)
		{
			write (1, "exit\n", 5);
			break ;
		}
		if (!is_valid_input(&shell))
			continue ;
		add_history(shell.line);
		if (!tokenize_input(&shell))
			continue ;
		if (!parse_tokens(&shell))
			continue ;
		run_execution (&shell);
		cleanup(&shell);
	}
	free_env(shell.env_list);
}
