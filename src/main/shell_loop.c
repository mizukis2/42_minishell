/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/09/13 00:00:46 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

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

static bool	handle_interruptions(t_shell *shell)
{
	if (!shell->line)
	{
		write(1, "exit\n", 5);
		return (true);
	}
	if (g_signal == SIGINT && shell->line && shell->line[0] == '\0')
	{
		shell->last_exit_code = 130;
		g_signal = 0;
		free(shell->line);
		shell->line = NULL;
	}
	return (false);
}

int	start_shell(char **envp)
{
	t_shell	shell;
	int		code;

	if (!init_shell(&shell, envp))
		return (1);
	while (1)
	{
		set_signals_prompt();
		shell.line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (handle_interruptions(&shell))
			break ;
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
	code = shell.last_exit_code;
	free_node_list(shell.env_list);
	return (code);
}
