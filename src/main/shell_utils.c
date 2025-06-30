/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:51:29 by zekhatib          #+#    #+#             */
/*   Updated: 2025/06/30 04:22:09 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace_or_empty(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			return (0);
		i++;
	}
	return (1);
}

bool	check_quotes(char *line)
{
	bool	in_quotes;
	char	quote;
	int		i;

	in_quotes = false;
	quote = 0;
	i = 0;
	while (line[i])
	{
		if (!in_quotes && (line[i] == '\'' || line[i] == '\"'))
		{
			quote = line[i];
			in_quotes = true;
		}
		else if (in_quotes && line[i] == quote)
			in_quotes = false;
		i++;
	}
	return (!in_quotes);
}

void	cleanup_shell(void)
{
	rl_clear_history();
}
