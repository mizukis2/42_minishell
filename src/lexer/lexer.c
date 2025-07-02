/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 05:44:32 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/02 11:36:49 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(const char *line)
{
	int				i;
	int				adv;
	char			c;
	const char		*start;
	t_token			*tokens;
	t_lexer_state	state;
	t_token_type	type;
	
	i = 0;
	adv = 0;
	start = NULL;
	tokens = NULL;
	state = STATE_START;
	while (line[i])
	{
		c = line[i];
		if (state == STATE_START)
		{
			if (ft_isspace(c))
				i++;
			else if (c == '\'')
			{
				state = STATE_IN_SINGLE_QUOTE;
				start = &line[++i];
			}
			else if (c == '\"')
			{
				state = STATE_IN_DOUBLE_QUOTE;
				start = &line[++i];
			}
			else if (is_metachar(c))
			{
				type = get_metachar_type(&line[i], &adv);
				add_token(&tokens, create_token(&line[i], adv, type));
				i += adv;
			}
			else
			{
				state = STATE_IN_WORD;
				start = &line[i++];
			}
		}
		else if (state == STATE_IN_WORD)
		{
			if (ft_isspace(c) || is_metachar(c) || c == '\'' || c == '\"')
			{
				add_token(&tokens, create_token(start, &line[i] - start, TOKEN_WORD));
				state = STATE_START;
			}
			else
				i++;
		}
		else if (state == STATE_IN_SINGLE_QUOTE)
		{
			if (c == '\'')
			{
				add_token(&tokens, create_token(start, &line[i] - start, TOKEN_WORD));
				state = STATE_START;
				i++;
			}
			else
				i++;
		}
		else if (state == STATE_IN_DOUBLE_QUOTE)
		{
			if (c == '\"')
			{
				add_token(&tokens, create_token(start, &line[i] - start, TOKEN_WORD));
				state = STATE_START;
				i++;
			}
			else
				i++;
		}
	}
	if (state == STATE_IN_WORD)
		add_token(&tokens, create_token(start, &line[i] - start, TOKEN_WORD));

	return (tokens);
}
