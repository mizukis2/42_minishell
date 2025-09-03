/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   heredoc_expansion.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/29 12:38:24 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/29 12:38:26 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_char_heredoc(t_expander *exp, const char *value,
	t_shell *shell)
{
	if (value[exp->i] == '$')
	{
		exp->i++;
		if (value[exp->i] == '?')
			handle_exit_status(&exp->i, &exp->result, shell);
		else
			handle_env_var(value, &exp->i, &exp->result, shell);
	}
	else
	{
		append_char_to_result(&exp->result, value[exp->i]);
		exp->i++;
	}
}

char	*expand_heredoc_variables(const char *value, t_shell *shell)
{
	t_expander	exp;

	exp.result = ft_strdup("");
	if (!exp.result)
		return (NULL);
	exp.i = 0;
	while (value[exp.i])
	{
		process_char_heredoc(&exp, value, shell);
	}
	return (exp.result);
}
