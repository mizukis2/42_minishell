/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/03 23:57:19 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_token *tokens)//for token debug
{
	while (tokens)
	{
		printf("\nTOKEN TYPE: %d, VALUE: [%s], Quote: [%d]\n",
			tokens->type, tokens->value, tokens->quote_type);
		tokens = tokens->next;
	}
}

static void	print_cmd(t_cmd *cmd)//for cmd debug
{
	int	i;
	int	cmd_count;

	cmd_count = 0;
	while (cmd)
	{
		printf("\nCommand #%d:\n", ++cmd_count);
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf("argv[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		printf("infile: %s\n", cmd->infile ? cmd->infile : "(null)");
		printf("outfile: %s\n", cmd->outfile ? cmd->outfile : "(null)");
		printf("append: %s\n", cmd->append ? "True" : "False");
		cmd = cmd->next;
	}
}

static int	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->exit_status = 0;
	shell->env_list = copy_initial_env(envp);
	if (!shell->env_list)
	{
		print_error("ERROR - Unable to make list of Environment Variables");
		shell->exit_status = 1;
		return (0);
	}
	return (1);
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
			break ;
		if (!is_valid_input(&shell))
			continue ;
		add_history(shell.line);
		if (!tokenize_input(&shell))
			continue ;
		if (!parse_tokens(&shell))
			continue ;
		if (shell.commands)
			print_cmd(shell.commands);//for debug
		if (shell.tokens)
			print_tokens(shell.tokens);//for debug
		cleanup(&shell);
	}
	free_node_list(shell.env_list);//maybe change the name to free_env?
}
