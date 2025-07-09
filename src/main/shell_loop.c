/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/04 01:43:20 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)//for debug
{
	while (tokens)
	{
		printf("TYPE: %d, VALUE: [%s]\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

t_token	*process_input(char *line)
{
	t_token	*tokens;

	tokens = lexer(line);
	if (!tokens)
	{
		printf("\e[0;31mSyntax error: Unable to make valid tokens\e[0m\n");
		free(line);
		return (NULL);
	}
	return (tokens);
}

void	enter_shell_loop(void)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (!line) // check for EOF Ctrl+D (temporary)
			break ;
		if (!is_valid_input(line))
			continue ;
		add_history(line);
		tokens = process_input(line);//!token
		if (tokens)
		{
			print_tokens(tokens);//for debug
			cleanup(tokens, line);
			tokens = NULL;
		}
	}
}
