/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 05:44:32 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/17 11:38:54 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	strip_quotes(char **old)
{
	size_t	len;
	char	*new;

	len = ft_strlen(*old);
	if (len >= 2)
	{
		new = malloc(len - 1);
		if (!new)
			return (false);
		ft_memcpy(new, *old + 1, len - 2);
		new[len - 2] = '\0';
		free(*old);
		*old = new;
	}
	return (true);
}

bool	set_quotes(t_token *token)
{
	int	i;

	if (token->type != TOKEN_WORD)
		return (true);
	i = ft_strlen(token->value);
	if (i < 2)
	{
		token->quote_type = QUOTE_NONE;
		return (true);
	}
	if (token->value[0] == '\'' && token->value[i - 1] == '\'')
		token->quote_type = QUOTE_SINGLE;
	else if (token->value[0] == '\"' && token->value[i - 1] == '\"')
		token->quote_type = QUOTE_DOUBLE;
	else
		token->quote_type = QUOTE_NONE;
	if (token->quote_type != QUOTE_NONE)
		if (!strip_quotes(&token->value))
			return (false);
	return (true);
}

bool	syntax_check(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current || current->type == TOKEN_PIPE)
		return (false);
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE)
				return (false);
		}
		else if (current->type != TOKEN_WORD)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
				return (false);
		}
		if (!set_quotes(current))
			return (false);
		current = current->next;
	}
	return (true);
}

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
		cleanup(tokens, line);
		tokens = NULL;
		return (NULL);
	}
	return (tokens);
}

t_token	*lexer(char *line)
{
	t_lex	lex;//echo "$USER"$USER'$USER'

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
