/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:38:56 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/17 11:41:09 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	make_token(t_lex *lex, int len, t_token_type type)
{
	lex->new_token = create_token(lex->start, len, type);
	if (!lex->new_token)
	{
		free_tokens(lex->tokens);
		return (false);
	}
	add_token(&lex->tokens, lex->new_token);
	return (true);
}

void	process_start(t_lex *lex, char *line)
{
	if (ft_isspace(lex->c))
		lex->i++;
	else if (is_metachar(lex->c))
	{
		lex->type = get_metachar_type(&line[lex->i], &lex->adv);
		lex->start = &line[lex->i];
		if (!make_token(lex, lex->adv, lex->type))
			return ;
		lex->i += lex->adv;
	}
	else
	{
		lex->state = STATE_IN_WORD;
		lex->start = &line[lex->i];
	}
}

void	process_inword(t_lex *lex, char *line)
{
	(void)line;
	if (lex->c == '\'')
	{
		lex->state = STATE_IN_SINGLE_QUOTE;
		lex->i++;
	}
	else if (lex->c == '\"')
	{
		lex->state = STATE_IN_DOUBLE_QUOTE;
		lex->i++;
	}
	else if (ft_isspace(lex->c) || is_metachar(lex->c))
	{
		if (!make_token(lex, &line[lex->i] - lex->start, TOKEN_WORD))
			return ;
		lex->state = STATE_START;
	}
	else
		lex->i++;
}

void	process_single_quotes(t_lex *lex)
{
	if (lex->c == '\'')
	{
		lex->state = STATE_IN_WORD;
		lex->i++;
	}
	else
		lex->i++;
}

void	process_double_quotes(t_lex *lex)
{
	if (lex->c == '\"')
	{
		lex->state = STATE_IN_WORD;
		lex->i++;
	}
	else
		lex->i++;
}
