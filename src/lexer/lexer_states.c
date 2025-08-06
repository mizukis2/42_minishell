/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:38:56 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 08:14:11 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	q;
	int		len;

	if (lex->c == '\'' || lex->c == '\"')
	{
		q = lex->c;
		lex->i++;
		while (line[lex->i] && line[lex->i] != q)
			lex->i++;
		if (line[lex->i] == q)
			lex->i++;
		return ;
	}
	if (ft_isspace(lex->c) || is_metachar(lex->c))
	{
		len = &line[lex->i] - lex->start;
		if (len > 0 && !make_token(lex, len, TOKEN_WORD))
			return ;
		lex->state = STATE_START;
		return ;
	}
	lex->i++;
}

void	process_single_quotes(t_lex *lex, char *line)
{
	if (lex->c == '\'')
	{
		if (should_make_token(lex, line))
			if (!make_token(lex, &line[lex->i] - lex->start + 1, TOKEN_WORD))
				return ;
		lex->state = STATE_IN_WORD;
		lex->start = &line[lex->i + 1];
		lex->i++;
	}
	else
		lex->i++;
}

void	process_double_quotes(t_lex *lex, char *line)
{
	if (lex->c == '\"')
	{
		if (should_make_token(lex, line))
			if (!make_token(lex, &line[lex->i] - lex->start + 1, TOKEN_WORD))
				return ;
		lex->state = STATE_IN_WORD;
		lex->start = &line[lex->i + 1];
		lex->i++;
	}
	else
		lex->i++;
}
