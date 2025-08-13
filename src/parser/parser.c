/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:01:57 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/04 00:00:07 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		if (r->is_heredoc && r->target)
			unlink(r->target);
		free(r->target);
		free(r);
		r = next;
	}
}

void free_single_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return;
	i = 0;
	while (cmd->argv[i])
	{
		free (cmd->argv[i]);
		i++;
	}
	free (cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd *next;
	while (cmd)
	{
		next = cmd->next;
		free_single_cmd(cmd);
		cmd = next;
	}
}

/* void	free_cmd_and_args(t_cmd *cmd, t_list *args)
{
	int	j;

	if (cmd)
	{
		if (cmd->argv)
		{
			j = 0;
			while (cmd->argv[j])
			{
				free(cmd->argv[j]);
				j++;
			}
			free(cmd->argv);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
	}
	ft_lstclear(&args, free);
} */

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

static bool	append_command(t_cmd **head, t_cmd **tail, t_cmd *new_cmd)
{
	if (!new_cmd)
		return (false);
	if (!*head)
		*head = new_cmd;
	else
		(*tail)->next = new_cmd;
	*tail = new_cmd;
	return (true);
}

void cleanup_parse(t_shell *shell, t_cmd *curr, t_cmd *head, char *msg)
{
	if (shell)
	{
		shell->commands = NULL;
		shell->last_exit_code = 2;
	}
	if (curr)
		free_single_cmd(curr);
	if (head)
		free_cmd_list(head);
	if (msg)
		print_error(msg);
}

bool	parse_tokens(t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*curr;
	t_token	*tokens;

	head = NULL;
	tail = NULL;
	curr = NULL;
	tokens = shell->tokens;
	if (tokens && tokens->type == TOKEN_PIPE)
		return (cleanup_parse(shell, NULL, head, "syntax error near unexpected token `|'"), false);
	while (tokens)
	{
		curr = parse_command(shell, &tokens);
		if (!curr)
			return (cleanup_parse(shell, NULL, head, NULL), false);
		if (curr->invalid)
			return (cleanup_parse(shell, curr, head, "Parsing Error - Unable to parse command"), false);
		if (!append_command(&head, &tail, curr))
			return (cleanup_parse(shell, curr, head, "Parsing Error - Unable to parse command"), false);
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			tokens = tokens->next;
			if (!tokens)
				return (cleanup_parse(shell, curr, head, "syntax error near unexpected token `|'"), false);
			if (tokens->type == TOKEN_PIPE)
				return (cleanup_parse(shell, curr, head, "syntax error near unexpected token `|'"), false);
		}
	}
	shell->commands = head;
	return (true);
}
