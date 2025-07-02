/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:38:56 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/02 15:53:52 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_start(t_lex *lex, const char *line)
{
	if (ft_isspace(lex->c))
		lex->i++;
	else if (lex->c == '\'')
	{
		lex->state = STATE_IN_SINGLE_QUOTE;
		lex->start = &line[++lex->i];
	}
	else if (lex->c == '\"')
	{
		lex->state = STATE_IN_DOUBLE_QUOTE;
		lex->start = &line[++lex->i];
	}
	else if (is_metachar(lex->c))
	{
		lex->type = get_metachar_type(&line[lex->i], &lex->adv);
		add_token(&lex->tokens,
			create_token(&line[lex->i], lex->adv, lex->type));
		lex->i += lex->adv;
	}
	else
	{
		lex->state = STATE_IN_WORD;
		lex->start = &line[lex->i++];
	}
}

void	process_in_inword(t_lex *lex, const char *line)
{
	if (ft_isspace(lex->c) || is_metachar(lex->c)
		|| lex->c == '\'' || lex->c == '\"')
	{
		add_token(&lex->tokens,
			create_token(lex->start, &line[lex->i] - lex->start, TOKEN_WORD));
		lex->state = STATE_START;
	}
	else
		lex->i++;
}

void	process_single_quotes(t_lex *lex, const char *line)
{
	if (lex->c == '\'')
	{
		add_token(&lex->tokens,
			create_token(lex->start, &line[lex->i] - lex->start, TOKEN_WORD));
		lex->state = STATE_START;
		lex->i++;
	}
	else
		lex->i++;
}

void	process_double_quotes(t_lex *lex, const char *line)
{
	if (lex->c == '\"')
	{
		add_token(&lex->tokens,
			create_token(lex->start, &line[lex->i] - lex->start, TOKEN_WORD));
		lex->state = STATE_START;
		lex->i++;
	}
	else
		lex->i++;
}
