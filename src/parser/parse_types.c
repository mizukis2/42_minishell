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

void	parse_word(t_token **tokens, t_list **args, t_cmd *cmd, t_shell *shell)
{
	t_token	*tok;
	char	*value;
	t_list	*node; //added for safety NULL check

	tok = *tokens;
	value = expand_variables(tok->value, shell);
	if (!value) 
	{
		shell->last_exit_code = 1;
		cmd->invalid = true;
		return ;
	}
	if (value[0] == '\0' && !tok->was_quoted)
		free(value);
	else
	{
		node = ft_lstnew(value);
		if (!node)
		{
			free (value);
			shell->last_exit_code = 1;
			cmd->invalid = true;
			return ;
		}
		ft_lstadd_back(args, node);
	}
	*tokens = (*tokens)->next;
}

bool is_redir (t_token_type tt)
{
	return (tt == TOKEN_REDIRECT_IN || tt == TOKEN_REDIRECT_OUT
			|| tt == TOKEN_APPEND || tt == TOKEN_HEREDOC);
}

t_cmd	*parse_command(t_shell *shell, t_token **tokens)
{
	t_cmd	*cmd;
	t_list	*args;
	t_token	*tok;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->invalid = false;
	args = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		tok = *tokens;
		if (tok->type == TOKEN_WORD)
			parse_word(tokens, &args, cmd, shell);
		else if (is_redir(tok->type))
			parse_redirection(tokens, cmd, shell);
		else
		{
			shell->last_exit_code = 2;
			cmd->invalid = true;
			break;
		}
	}
	cmd->argv = argslst_to_array(args);
	ft_lstclear(&args, free);
	return (cmd);
}

