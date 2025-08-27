/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_redirection_utils.c                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/15 14:28:35 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/15 14:28:36 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*add_redir(t_redir **head, t_rtype type, char *filename,
						bool is_heredoc)
{
	t_redir	*new;
	t_redir	*tmp;

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

char	*expect_and_expand(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	char	*str;

	if (!tokens || !*tokens || (*tokens)->type != TOKEN_WORD)
	{
		set_invalid(cmd, shell, 2);
		return (NULL);
	}
	str = expand_variables((*tokens)->value, shell);
	if (!str)
	{
		set_invalid(cmd, shell, 1);
		return (NULL);
	}
	(*tokens) = (*tokens)->next;
	return (str);
}
