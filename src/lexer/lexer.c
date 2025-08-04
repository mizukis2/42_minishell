/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 05:44:32 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/23 00:10:05 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_input(char *line)
{
	t_token	*tokens;

	tokens = lexer(line);
	if (!tokens)
	{
		printf("\e[0;31mSyntax error: Unable to make valid tokens\e[0m\n");
		free(line);
		return (NULL);
	}
	if (!syntax_check(tokens))
	{
		printf("\e[0;31mSyntax error\e[0m\n");
		free_tokens(tokens); //changed from cleanup(tokens, line)
		free (line);
		tokens = NULL;
		return (NULL);
	}
	return (tokens);
}

void	lexer_init(t_lex *lex, char *line)
{
	lex->i = 0;
	lex->adv = 0;
	lex->c = 0;
	lex->line = line;
	lex->start = NULL;
	lex->tokens = NULL;
	lex->new_token = NULL;
	lex->state = STATE_START;
}

t_token	*lexer(char *line)
{
	t_lex	lex;

	lexer_init(&lex, line);
	while (line[lex.i])
	{
		lex.c = line[lex.i];
		if (lex.state == STATE_START)
			process_start(&lex, line);
		else if (lex.state == STATE_IN_WORD)
			process_inword(&lex, line);
		else if (lex.state == STATE_IN_SINGLE_QUOTE)
			process_single_quotes(&lex, line);
		else if (lex.state == STATE_IN_DOUBLE_QUOTE)
			process_double_quotes(&lex, line);
	}
	if (lex.state == STATE_IN_WORD && should_make_token(&lex, line))
		if (!make_token(&lex, &line[lex.i] - lex.start, TOKEN_WORD))
			return (NULL);
	return (lex.tokens);
}
