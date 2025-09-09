/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:38:24 by mmatsui           #+#    #+#             */
/*   Updated: 2025/09/07 04:51:10 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	char_heredoc(t_expander *exp, const char *val, t_shell *shell)
{
	if (val[exp->i] == '$')
	{
		exp->i++;
		if (val[exp->i] == '?')
			handle_exit_status(&exp->i, &exp->result, shell);
		else
			handle_env_var(val, &exp->i, &exp->result, shell);
	}
	else
	{
		append_char_to_result(&exp->result, val[exp->i]);
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
		char_heredoc(&exp, value, shell);
	}
	return (exp.result);
}
