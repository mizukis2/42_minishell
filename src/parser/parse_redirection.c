/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_redirection.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/13 11:28:12 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/13 11:28:13 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool str_contains_ifs(const char *s)
{
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\n')
			return true;
		s++;
	}
	return false;
}

static bool is_ambiguous(const char *expanded_word)
{
	if (!expanded_word || expanded_word[0] == '\0')
		return true;
	if (str_contains_ifs(expanded_word))
		return true;
	return false;
}

static t_rtype map_redir_type(t_token_type tt)
{
	if (tt == TOKEN_REDIRECT_IN)
		return (R_IN);
	if (tt == TOKEN_REDIRECT_OUT)
		return (R_OUT);
	if (tt == TOKEN_APPEND)
		return (R_APPEND);
	if (tt == TOKEN_HEREDOC)
		return (R_HEREDOC);
	return (R_IN);
}

void	parse_redirection(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_token_type tt;
	char *word;

	if (!tokens || !*tokens)
	{
		cmd->invalid = true;
		shell->last_exit_code = 2;
		return ;
	}
	if (cmd->invalid)
		return;
	tt = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (tt == TOKEN_HEREDOC)
		return (handle_heredoc_redir(tokens, cmd, shell));
	word = expect_and_expand(tokens, shell, cmd);
	if (!word)
	{
		cmd->invalid = true;
		return ;
	}
	if (is_ambiguous(word))
	{
		print_error_builtin("ambigious redirect\n");
		shell->last_exit_code = 1;
		cmd->invalid = true;
		free(word);
		return ;
	}
	if (!add_redir(&cmd->redirs, map_redir_type(tt), word, false))
	{
		free(word);
		shell->last_exit_code = 1;
		cmd->invalid = true;
		return ;
	}
		free (word);
}
