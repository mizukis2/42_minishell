/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/16 02:38:24 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)//for token debug
{
	while (tokens)
	{
		printf("TYPE: %d, VALUE: [%s], Quote: [%d]\n", tokens->type, tokens->value, tokens->quote_type);
		tokens = tokens->next;
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
		commands = parse_tokens(tokens);//null check pending
		if (tokens)
		{
			print_tokens(tokens);//for debug
			cleanup(tokens, line);
			tokens = NULL;
		}
		else
			continue ;
	}
}
