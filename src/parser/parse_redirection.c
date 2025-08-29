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

static bool	is_ambiguous(const char *expanded_word)
{
	if (!expanded_word || expanded_word[0] == '\0')
		return (true);
	return (false);
}

static t_rtype	map_redir_type(t_token_type tt)
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

static void	redir_error_set_free(t_cmd *cmd, t_shell *shell, int code,
									char *str)
{
	free (str);
	set_invalid(cmd, shell, code);
}

void	parse_redirection(t_token **tok_it, t_cmd *cmd, t_shell *shell)
{
	t_token_type	tt;
	char			*word;

	if (!tok_it || !*tok_it)
		return (set_invalid(cmd, shell, 2));
	if (cmd->invalid)
		return ;
	tt = (*tok_it)->type;
	*tok_it = (*tok_it)->next;
	if (tt == TOKEN_HEREDOC)
		return (handle_heredoc_redir(tok_it, cmd, shell));
	word = expect_and_expand(tok_it, shell, cmd);
	if (!word)
		return (set_invalid(cmd, shell, 1));
	if (is_ambiguous(word))
	{
		print_error_builtin("ambiguous redirect\n");
		return (redir_error_set_free(cmd, shell, 1, word));
	}
	if (!add_redir(&cmd->redirs, map_redir_type(tt), word, false))
		return (redir_error_set_free(cmd, shell, 1, word));
	free (word);
}
