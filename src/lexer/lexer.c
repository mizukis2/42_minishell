/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 05:44:32 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/09 18:57:28 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *line)
{
	t_lex	lex;

	lex.i = 0;
	lex.adv = 0;
	lex.c = 0;
	lex.start = NULL;
	lex.tokens = NULL;
	lex.new_token = NULL;
	lex.state = STATE_START;
	while (line[lex.i])
	{
		lex.c = line[lex.i];
		if (lex.state == STATE_START)
			process_start(&lex, line);
		else if (lex.state == STATE_IN_WORD)
			process_inword(&lex, line);
		else if (lex.state == STATE_IN_SINGLE_QUOTE)
			process_single_quotes(&lex);
		else if (lex.state == STATE_IN_DOUBLE_QUOTE)
			process_double_quotes(&lex);
	}
	if (lex.state == STATE_IN_WORD)
		if (!make_token(&lex, lex.i - (lex.start - line), TOKEN_WORD))
			return (NULL);
	return (lex.tokens);
}
