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

static void	print_tokens(t_token *tokens)//for token debug
{
	while (tokens)
	{
		printf("TOKEN TYPE: %d, VALUE: [%s]\n",
			tokens->type, tokens->value);
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

/* mizuki's update
void	enter_shell_loop(char **envp)
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (perror("malloc failed"));
	if (!init_shell(shell, envp))
		return ;
	
	while (1)
	{
		shell->line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (!shell->line) // check for EOF Ctrl+D (temporary)
			break ;
		if (!is_valid_input(shell->line))
		{
			free(shell->line);
			continue ;
		}
		add_history(shell->line);
		shell->tokens = tokenize_input(shell->line);
		shell->commands = parse_tokens(shell->tokens);
		shell->last_exit_code = execute(shell);
		printf ("exit code : %d\n", shell->last_exit_code); //for debug
		print_cmd(shell->commands);//for debug
		print_tokens(shell->tokens);//for debug
		clean_shell(shell);
	}
	free_node_list(shell->envp);
	free (shell);
}
*/

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
    //exit_code = execute(commands, shell);
		//shell->last_exit_code = exit_code;
		//printf ("exit code : %d\n", shell->last_exit_code);
		cleanup(&shell);
	}
	free_node_list(shell.env_list);//maybe change the name to free_env?
}
