/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:01:57 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/16 06:34:47 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*free_and_error(t_cmd *cmd, t_list *args, char *msg)
{
	return (NULL);
}

void	free_cmd(t_cmd *cmd)
{
	
}

char	**argvlst_to_array(t_list *args)
{
	
}

t_cmd	*parse_command(t_token **tokens)
{
	t_cmd	*cmd;
	t_list	*args;
	t_token	*tok;

	cmd = ft_calloc(1, sizeof(t_cmd));
	args = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		tok = *tokens;
		if (tok->type == TOKEN_WORD)
			ft_lstadd_back(&args, ft_lstnew(ft_strdup(tok->value)));
		else if (tok->type == TOKEN_REDIRECT_IN || tok->type == TOKEN_HEREDOC)
		{
			*tokens = (*tokens)->next;
			if (!*tokens || (*tokens)->type != TOKEN_WORD)
				return (free_and_error(cmd, args, ">"));
			cmd->infile = ft_strdup((*tokens)->value);
		}
		else if (tok->type == TOKEN_REDIRECT_OUT || tok->type == TOKEN_APPEND)
		{
			cmd->append = (tok->type == TOKEN_APPEND);
			*tokens = (*tokens)->next;
			if (!*tokens || (*tokens)->type != TOKEN_WORD)
				return (free_and_error(cmd, args, "<"));
			cmd->outfile = ft_strdup((*tokens)->value);
		}
		*tokens = (*tokens)->next;
	}
	cmd->argv = argvlst_to_array(args);
	ft_lstclear(&args, free);
	return (cmd);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*curr;

	head = NULL;
	tail = NULL;
	curr = NULL;
	while (tokens)
	{
		curr = parse_command(&tokens);
		if (!curr)
		{
			free_cmd(head);
			return (NULL);
		}
		if (!head)
			head = curr;
		else
			tail->next = curr;
		tail = curr;
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head);
}
