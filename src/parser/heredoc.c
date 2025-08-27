/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:45:45 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 09:12:27 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//signal memo
//shell->last_exit_code = 130
//unlink (heredoc.temp_path)
//return NULL

void	set_invalid(t_cmd *cmd, t_shell *shell, int code)
{
	cmd->invalid = true;
	if (code >= 0)
		shell->last_exit_code = code;
}

static char	*expect_delim_no_expand(t_token **tokens, t_shell *shell,
										t_cmd *cmd)
{
	char	*str;

	if (!tokens || !*tokens || (*tokens)->type != TOKEN_WORD)
	{
		set_invalid(cmd, shell, 2);
		return (NULL);
	}
	str = ft_strdup((*tokens)->value);
	if (!str)
	{
		set_invalid(cmd, shell, 1);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	return (str);
}

void	handle_heredoc_redir(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_token	*tok;
	char	*delim;
	char	*path;

	tok = *tokens;
	delim = expect_delim_no_expand(tokens, shell, cmd);
	if (!delim)
		return (set_invalid(cmd, shell, 2));
	path = create_heredoc_file(delim, shell);
	free(delim);
	if (!path)
		return (set_invalid(cmd, shell, 1));
	if (!add_redir(&cmd->redirs, R_HEREDOC, path, true))
	{
		free(path);
		return (set_invalid(cmd, shell, 1));
	}
	free (path);
}
