/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:22:44 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 08:54:06 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit_status(int *i, char **result, t_shell *shell)
{
	char	*status;

	status = ft_itoa(shell->last_exit_code);
	append_to_result(result, status);
	free(status);
	(*i)++;
}

static void	handle_env_var(const char *value, int *i,
	char **result, t_shell *shell)
{
	int		len;
	char	*key;
	char	*val;

	len = var_len(&value[*i]);
	if (len == 0)
	{
		append_char_to_result(result, '$');
		return ;
	}
	key = ft_substr(value, *i, len);
	if (!key)
		return ;
	val = get_env_value(shell->env_list, key);
	if (val)
		append_to_result(result, val);
	free (val);
	free (key);
	*i += len;
}

static void	process_char(t_expander *exp, const char *value, t_shell *shell)
{
	if (value[exp->i] == '\'' && !exp->in_double_quote)
	{
		exp->in_single_quote = !exp->in_single_quote;
		exp->i++;
	}
	else if (value[exp->i] == '\"' && !exp->in_single_quote)
	{
		exp->in_double_quote = !exp->in_double_quote;
		exp->i++;
	}
	else if (value[exp->i] == '$' && !exp->in_single_quote)
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

char	*expand_variables(const char *value, t_shell *shell)
{
	t_expander	exp;

	exp.result = ft_strdup("");
	if (!exp.result)
		return (NULL);
	exp.i = 0;
	exp.in_single_quote = false;
	exp.in_double_quote = false;
	while (value[exp.i])
	{
		process_char(&exp, value, shell);
	}
	return (exp.result);
}
