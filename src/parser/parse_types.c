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

	tok = *tokens;
	value = expand_variables(tok->value, shell);
	if (!value)
	{
		free_cmd_and_args(cmd, *args);
		return ;
	}
	ft_lstadd_back(args, ft_lstnew(value));
	*tokens = (*tokens)->next;
}

void	parse_redirect_in(t_token **tokens, t_list **args,
	t_cmd *cmd, t_shell *shell)
{
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free_cmd_and_args(cmd, *args);
		return ;
	}
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = expand_variables((*tokens)->value, shell);
	if (!cmd->infile)
	{
		free_cmd_and_args(cmd, *args);
		return ;
	}
	*tokens = (*tokens)->next;
}

void	parse_redirect_o(t_token **tokens, t_list **args,
	t_cmd *cmd, t_shell *shell)
{
	t_token	*tok;

	tok = *tokens;
	cmd->append = (tok->type == TOKEN_APPEND);
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free_cmd_and_args(cmd, *args);
		return ;
	}
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = expand_variables((*tokens)->value, shell);
	if (!cmd->outfile)
	{
		free_cmd_and_args(cmd, *args);
		return ;
	}
	*tokens = (*tokens)->next;
}

void	parse_heredoc(t_token **tokens, t_list **args,
	t_cmd *cmd, t_shell *shell)
{
	t_token	*next;
	char	*delim;
	char	*temp_path;

	next = (*tokens)->next;
	if (!next || next->type != TOKEN_WORD)
		return (free_cmd_and_args(cmd, *args));
	delim = next->value;
	temp_path = create_heredoc_file(delim, shell);
	if (!temp_path)
		return (free_cmd_and_args(cmd, *args));
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = temp_path;
	cmd->heredoc = true;
	*tokens = next->next;
}

t_cmd	*parse_command(t_shell *shell, t_token **tokens)
{
	t_cmd	*cmd;
	t_list	*args;
	t_token	*tok;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	args = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		tok = *tokens;
		if (tok->type == TOKEN_WORD)
			parse_word(tokens, &args, cmd, shell);
		else if (tok->type == TOKEN_REDIRECT_IN)
			parse_redirect_in(tokens, &args, cmd, shell);
		else if (tok->type == TOKEN_REDIRECT_OUT || tok->type == TOKEN_APPEND)
			parse_redirect_o(tokens, &args, cmd, shell);
		else if (tok->type == TOKEN_HEREDOC)
			parse_heredoc(tokens, &args, cmd, shell);
	}
	cmd->argv = argslst_to_array(args);
	ft_lstclear(&args, free);
	return (cmd);
}
