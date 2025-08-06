/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 06:02:52 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/28 02:49:40 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_metachar_type(char *str, int *advance)
{
	if (ft_strncmp (str, "<<", 2) == 0)
		return (*advance = 2, TOKEN_HEREDOC);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (*advance = 2, TOKEN_APPEND);
	else if (str[0] == '<')
		return (*advance = 1, TOKEN_REDIRECT_IN);
	else if (str[0] == '>')
		return (*advance = 1, TOKEN_REDIRECT_OUT);
	else if (str[0] == '|')
		return (*advance = 1, TOKEN_PIPE);
	return (*advance = 1, TOKEN_WORD);
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
		current = current->next;
	}
	return (true);
}
