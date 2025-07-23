/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:01:57 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/23 03:07:14 by zekhatib         ###   ########.fr       */
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
		free(cmd->heredoc_delim);
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
		free(cmd->heredoc_delim);
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
	if (!cmd)
		return (NULL);
	cmd->heredoc_fd = -1;
	args = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		tok = *tokens;
		if (tok->type == TOKEN_WORD)
			parse_word(tokens, &args, cmd);
		else if (tok->type == TOKEN_REDIRECT_IN)
			parse_redirect_in(tokens, &args, cmd);
		else if (tok->type == TOKEN_REDIRECT_OUT || tok->type == TOKEN_APPEND)
			parse_redirect_o(tokens, &args, cmd);
		else if (tok->type == TOKEN_HEREDOC)
			parse_heredoc(tokens, &args, cmd);
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
