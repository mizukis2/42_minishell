/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:22:44 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/04 04:52:10 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit_status(int *i, char **result, t_shell *shell)
{
	char	*status;

	status = ft_itoa(shell->exit_status);
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
	}
	else
	{
		key = ft_substr(value, *i, len);
		val = get_env_value(shell->env_list, key);
		if (!val)
			append_to_result(result, "");
		else
		{
			append_to_result(result, val);
			free(val);
		}
		free(key);
		*i += len;
	}
}

static void	handle_dollar(const char *value, int *i,
	char **result, t_shell *shell)
{
	(*i)++;
	if (value[*i] == '?')
		handle_exit_status(i, result, shell);
	else
		handle_env_var(value, i, result, shell);
}

static void	handle_normal_char(const char *value, int *i, char **result)
{
	append_char_to_result(result, value[*i]);
	(*i)++;
}

char	*expand_variables(const char *value, t_shell *shell)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			handle_dollar(value, &i, &result, shell);
		else
			handle_normal_char(value, &i, &result);
	}
	return (result);
}
