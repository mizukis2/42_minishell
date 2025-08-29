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

static void	init_cmd_nodes(t_cmd **head, t_cmd **tail, t_cmd **curr)
{
	*head = NULL;
	*tail = NULL;
	*curr = NULL;
}

static bool	process_command(t_parser *p)
{
	*(p->curr) = parse_command(p->shell, p->tok_it);
	if (!*(p->curr))
		return (cleanup_parse(p->shell, NULL, *(p->head), NULL), false);
	if ((*(p->curr))->invalid)
		return (cleanup_parse(p->shell, *(p->curr), *(p->head), NULL), false);
	if (!append_command(p->head, p->tail, *(p->curr)))
		return (cleanup_parse(p->shell, *(p->curr), *(p->head), ERR_SYN_APP),
			false);
	if (*(p->tok_it) && (*(p->tok_it))->type == TOKEN_PIPE)
	{
		*(p->tok_it) = (*(p->tok_it))->next;
		if (!*(p->tok_it) || (*(p->tok_it))->type == TOKEN_PIPE)
			return (cleanup_parse(p->shell, *(p->curr), *(p->head),
					ERR_SYN_PIPE), false);
	}
	return (true);
}

bool	parse_tokens(t_shell *shell)
{
	t_cmd		*head;
	t_cmd		*tail;
	t_cmd		*curr;
	t_token		*cur_tok;
	t_parser	p;

	init_cmd_nodes(&head, &tail, &curr);
	cur_tok = shell->tokens;
	if (cur_tok && cur_tok->type == TOKEN_PIPE)
		return (cleanup_parse(shell, NULL, head, ERR_SYN_PIPE), false);
	p.shell = shell;
	p.head = &head;
	p.tail = &tail;
	p.curr = &curr;
	p.tok_it = &cur_tok;
	while (cur_tok)
	{
		if (!process_command(&p))
			return (false);
	}
	shell->commands = head;
	return (true);
}
