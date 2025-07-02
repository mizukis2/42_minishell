/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/02 06:47:58 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TYPE: %d, VALUE: [%s]\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
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
		if (is_whitespace_or_empty(line))
		{
			free(line);
			continue ;
		}
		add_history (line);
		if (!check_quotes(line))
		{
			printf("\e[0;31mSyntax error: Unclosed Quotes\e[0m\n");
			free(line);
			continue ;
		}
		tokens = lexer(line);
		print_tokens(tokens);
		if (!tokens)
		{
			printf("\e[0;31mSyntax error: Unable to make valid tokens\e[0m\n");
			free(line);
			continue ;
		}
		free(line);
	}
}
