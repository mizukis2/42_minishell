/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 05:44:32 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/02 15:55:49 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(const char *line)
{
	t_lex	lex;

	lex.i = 0;
	lex.adv = 0;
	lex.c = 0;
	lex.start = NULL;
	lex.tokens = NULL;
	lex.state = STATE_START;
	while (line[lex.i])
	{
		lex.c = line[lex.i];
		if (lex.state == STATE_START)
			process_start(&lex, line);
		else if (lex.state == STATE_IN_WORD)
			process_in_inword(&lex, line);
		else if (lex.state == STATE_IN_SINGLE_QUOTE)
			process_single_quotes(&lex, line);
		else if (lex.state == STATE_IN_DOUBLE_QUOTE)
			process_double_quotes(&lex, line);
	}
	if (lex.state == STATE_IN_WORD)
		add_token(&lex.tokens,
			create_token(lex.start, &line[lex.i] - lex.start, TOKEN_WORD));
	return (lex.tokens);
}
