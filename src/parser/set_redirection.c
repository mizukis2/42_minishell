/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   set_redirection.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/13 11:28:12 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/13 11:28:13 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool str_contains_ifs(const char *s)
{
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\n')
			return true;
		s++;
	}
	return false;
}

bool is_ambiguous(const char *expanded_word)
{
	if (!expanded_word || expanded_word[0] == '\0')
		return true;
	if (str_contains_ifs(expanded_word))
		return true;
	return false;
}


t_rtype map_redir_type(t_token_type tt)
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

t_redir *add_redir(t_redir **head, t_rtype type, char *filename, bool is_heredoc)
{
	t_redir *new;
	t_redir *tmp;
	
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = type;
	new->target = ft_strdup(filename);
	if (!new->target)
		return (free (new), NULL);
	new->is_heredoc = is_heredoc;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

char *expect_delim_no_expand(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	char *str;

	if (!tokens || (*tokens)->type != TOKEN_WORD)
	{
		shell->last_exit_code = 2;
		cmd->invalid = true;
		return NULL;
	}
	str = ft_strdup((*tokens)->value);
	*tokens = (*tokens)->next;
	if (!str)
		cmd->invalid = true;
	return (str);
}

char *expect_and_expand(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	char *str;

	if (!tokens || (*tokens)->type != TOKEN_WORD)
	{
		shell->last_exit_code = 2;
		cmd->invalid = true;
		return NULL;
	}
	str = expand_variables((*tokens)->value, shell);
	(*tokens) = (*tokens)->next;
	if (!str)
		cmd->invalid = true;
	return(str);
}

char *collect_here_temp(const char *delim, t_shell *shell, t_cmd *cmd)
{
	char *path;

	path = create_heredoc_file(delim, shell);
	if (!path)
		cmd->invalid = true;
	return (path);
}

void parse_redirection(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_token_type tt;
	char *word;
	char *path;

	if (!tokens || !*tokens)
	{
		cmd->invalid = true;
		shell->last_exit_code = 2;
		return ;
	}
	tt = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (cmd->invalid)
		return;
	if (tt == TOKEN_HEREDOC)
	{
		word = expect_delim_no_expand(tokens, shell,  cmd);
		if (!word)
		{
			cmd->invalid = true;
			return ;
		}
		path = collect_here_temp(word, shell, cmd);
		free(word);
		if (!path)
		{
			cmd->invalid = true;
			return ;
		}
		if (!add_redir(&cmd->redirs, R_HEREDOC, path, true))
		{
			free(path);
			cmd->invalid = true;
			return ;
		}
		free (path);
		return ;
	}
	word = expect_and_expand(tokens, shell, cmd);
	if (!word)
	{
		cmd->invalid = true;
		return ;
	}
	if (is_ambiguous(word))
	{
		print_error_builtin("ambigious reduction\n");
		free(word);
		cmd->invalid = true;
		return ;
	}
	if (!add_redir(&cmd->redirs, map_redir_type(tt), word, false))
	{
		free(word);
		cmd->invalid = true;
		return ;
	}
		free (word);
}
