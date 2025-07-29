/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/23 03:56:10 by zekhatib         ###   ########.fr       */
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

static void	print_cmd(t_cmd *cmd)
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
        if (cmd->heredoc_delim)
            printf("heredoc_delim: %s\n", cmd->heredoc_delim);
        printf("append: %s\n", cmd->append ? "True" : "False");
        cmd = cmd->next;
    }
}

void	enter_shell_loop(char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*commands;
	t_shell *shell;
	int		exit_code;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (perror("malloc failed"));
	shell->envp = copy_initial_env(envp);
	if (!shell->envp)
		return (perror("copy_initial_env failed"));
	while (1)
	{
		line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (!line) // check for EOF Ctrl+D (temporary)
			break ;
		if (!is_valid_input(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = tokenize_input(line);
		commands = parse_tokens(tokens);
		if (commands)
		{
			print_cmd(commands);//for debug
			exit_code = execute(commands, shell);
			shell->last_exit_code = exit_code;
			printf ("exit code : %d\n", shell->last_exit_code);
			free_cmd_list(commands);
		}
		if (tokens)
		{
			print_tokens(tokens);//for debug
			cleanup(tokens, line);
		}
	}
	free_node_list(shell->envp);
	free (shell);
}
