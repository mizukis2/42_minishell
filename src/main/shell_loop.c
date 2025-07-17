/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/17 08:01:39 by zekhatib         ###   ########.fr       */
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

static void	print_cmd(t_cmd *cmd)//for command debug
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv[i])
		{
			printf("argv[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
		printf("infile: %s\n", cmd->infile);
		printf("outfile: %s\n", cmd->outfile);
		if (cmd->append)
			printf("append: True\n\n");
		else
			printf("append: false\n\n");
		cmd = cmd->next;
	}
}

void	enter_shell_loop(void)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*commands;

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
			print_cmd(commands);
			free_cmd_list(commands);
		}
		if (tokens)
		{
			print_tokens(tokens);//for debug
			cleanup(tokens, line);
		}
		else
			continue ;
	}
}
