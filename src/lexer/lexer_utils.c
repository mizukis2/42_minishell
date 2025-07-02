/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 06:02:52 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/02 06:58:56 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_metachar_type(const char *str, int *advance)
{
	if (ft_strncmp (str, "<<", 2) == 0)
		return (*advance = 2, TOKEN_HEREDOC);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (*advance = 2, TOKEN_APPEND);
	else if (str[0] == '<')
		return (*advance = 1, TOKEN_REDIRECT_IN);
	else if (str[0] == '>')
		return (*advance = 1, TOKEN_REDIRECT_OUT);
	else
		return (*advance = 1, TOKEN_PIPE);
}

t_token	*create_token(const char *start, int len, t_token_type type)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strndup(start, len);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*curr = *head;
	if (!curr)
	{
		*head = new_token;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = new_token;
}
