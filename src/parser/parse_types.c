/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:34:57 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 09:15:23 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_word(t_token **tok_it, t_list **args, t_cmd *cmd, t_shell *shell)
{
	const t_token	*tok_cur;
	char			*value;
	t_list			*node;

	tok_cur = *tok_it;
	value = expand_variables(tok_cur->value, shell);
	if (!value)
		return (set_invalid(cmd, shell, 1));
	if (value[0] == '\0' && !tok_cur->was_quoted)
		free(value);
	else
	{
		node = ft_lstnew(value);
		if (!node)
		{
			free (value);
			return (set_invalid(cmd, shell, 1));
		}
		ft_lstadd_back(args, node);
	}
	*tok_it = (*tok_it)->next;
}

bool	is_redir(t_token_type tt)
{
	return (tt == TOKEN_REDIRECT_IN || tt == TOKEN_REDIRECT_OUT
		|| tt == TOKEN_APPEND || tt == TOKEN_HEREDOC);
}

t_cmd	*parse_command(t_shell *shell, t_token **tok_it)
{
	t_cmd	*cmd;
	t_list	*args;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->invalid = false;
	args = NULL;
	while (*tok_it && (*tok_it)->type != TOKEN_PIPE)
	{
		if ((*tok_it)->type == TOKEN_WORD)
			parse_word(tok_it, &args, cmd, shell);
		else if (is_redir((*tok_it)->type))
			parse_redirection(tok_it, cmd, shell);
		else
		{
			set_invalid(cmd, shell, 2);
			break ;
		}
	}
	cmd->argv = argslst_to_array(args);
	ft_lstclear(&args, free);
	return (cmd);
}
