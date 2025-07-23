/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:34:57 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/23 03:57:18 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_word(t_token **tokens, t_list **args, t_cmd *cmd)
{
	t_token	*tok;
	char	*value;

	tok = *tokens;
	if (tok->value[0] == '\0')
		value = ft_strdup("");
	else if (tok->quote_type == QUOTE_SINGLE)
		value = ft_strdup(tok->value);
	else
		value = ft_strdup(tok->value);
		// value = expand_variables(tok->value, envp, last_status);
	if (!value)
	{
		free_and_error(cmd, *args);
		return ;
	}
	ft_lstadd_back(args, ft_lstnew(value));
	*tokens = (*tokens)->next;
}

void	parse_redirect_in(t_token **tokens, t_list **args, t_cmd *cmd)
{
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free_and_error(cmd, *args);
		return ;
	}
	if (cmd->infile)
		free(cmd->infile);
	if ((*tokens)->quote_type == QUOTE_SINGLE)
		cmd->infile = ft_strdup((*tokens)->value);
	else
		cmd->infile = ft_strdup((*tokens)->value);
		//expand_variables((*tokens)->value, envp, last_status);
	if (!cmd->infile)
	{
		free_and_error(cmd, *args);
		return ;
	}
	*tokens = (*tokens)->next;
}

void	parse_redirect_o(t_token **tokens, t_list **args, t_cmd *cmd)
{
	t_token	*tok;

	tok = *tokens;
	cmd->append = (tok->type == TOKEN_APPEND);
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free_and_error(cmd, *args);
		return ;
	}
	if (cmd->outfile)
		free(cmd->outfile);
	if ((*tokens)->quote_type == QUOTE_SINGLE)
		cmd->outfile = ft_strdup((*tokens)->value);
	else
		cmd->outfile = ft_strdup((*tokens)->value);
		//expand_variables((*tokens)->value, envp, last_status);
	if (!cmd->outfile)
	{
		free_and_error(cmd, *args);
		return ;
	}
	*tokens = (*tokens)->next;
}

void	parse_heredoc(t_token **tokens, t_list **args, t_cmd *cmd)
{
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free_and_error(cmd, *args);
		return ;
	}
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup((*tokens)->value);
	if (!cmd->heredoc_delim)
	{
		free_and_error(cmd, *args);
		return ;
	}
	cmd->herdoc_expand = ((*tokens)->quote_type == QUOTE_NONE);
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	*tokens = (*tokens)->next;
}
