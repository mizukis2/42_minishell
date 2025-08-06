/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 05:44:32 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/02 01:39:16 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tokenize_input(t_shell *shell)
{
	shell->tokens = lexer(shell->line);
	if (!shell->tokens)
	{
		print_error("Syntax error - Unable to make valid tokens");
		shell->last_exit_code = 2;
		free(shell->line);
		return (false);
	}
	if (!syntax_check(shell->tokens))
	{
		print_error("Syntax error - Invalid syntax grammar");
		shell->last_exit_code = 2;
		cleanup(shell);
		shell->tokens = NULL;
		return (false);
	}
	return (true);
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
