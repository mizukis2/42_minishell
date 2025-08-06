/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:59:32 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/23 00:15:53 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *start, int len, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strndup(start, len);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*curr;

	curr = *head;
	if (!curr)
	{
		*head = new_token;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = new_token;
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
	head = NULL;
}

bool	should_make_token(t_lex *lex, char *line)
{
	return (lex->start && lex->start < &line[lex->i]);
}

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
