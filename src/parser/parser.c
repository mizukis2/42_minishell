/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:01:57 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/16 12:14:09 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		cmd = temp;
	}
}

t_cmd	*free_and_error(t_cmd *cmd, t_list *args)
{
	printf("syntax error near unexpected token\n");
	if (cmd)
	{
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
	}
	ft_lstclear(&args, free);
	return (NULL);
}

char	**argslst_to_array(t_list *args)
{
	char	**argv;
	t_list	*curr;
	int		size;
	int		i;

	size = ft_lstsize(args);
	argv = malloc((size + 1) * sizeof(char *));
	curr = args;
	i = 0;
	if (!argv)
		return (NULL);
	while (curr)
	{
		argv[i] = ft_strdup(curr->content);
		i++;
		curr = curr->next;
	}
	argv[i] = NULL;
	return (argv);
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
				return (free_and_error(cmd, args));
			cmd->infile = ft_strdup((*tokens)->value);
		}
		else if (tok->type == TOKEN_REDIRECT_OUT || tok->type == TOKEN_APPEND)
		{
			cmd->append = (tok->type == TOKEN_APPEND);
			*tokens = (*tokens)->next;
			if (!*tokens || (*tokens)->type != TOKEN_WORD)
				return (free_and_error(cmd, args));
			cmd->outfile = ft_strdup((*tokens)->value);
		}
		*tokens = (*tokens)->next;
	}
	cmd->argv = argslst_to_array(args);
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
			free_cmd_list(head);
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
