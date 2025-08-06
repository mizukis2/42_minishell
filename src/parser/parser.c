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
				cmd->argv[i] = NULL;
				i++;
			}
			free(cmd->argv);
			cmd->argv = NULL;
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = temp;
	}
}

void	free_cmd_and_args(t_cmd *cmd, t_list *args)
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
	while (tokens)
	{
		curr = parse_command(shell, &tokens);
		if (!append_command(&head, &tail, curr))
		{
			print_error("Parsing Error - Unable to parse command");
			free_cmd_list(head);
			shell->commands = NULL;
			shell->last_exit_code = 2;
			return (false);
		}
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	shell->commands = head;
	return (true);
}
