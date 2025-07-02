/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:51:29 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/02 13:26:32 by zekhatib         ###   ########.fr       */
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

bool	is_valid_input(char *line)
{
	if (is_whitespace_or_empty(line))
	{
		free(line);
		return (false);
	}
	return (true);
}

bool	check_and_handle_quotes(char *line)
{
	if (!check_quotes(line))
	{
		printf("\e[0;31mSyntax error: Unclosed Quotes\e[0m\n");
		add_history(line);
		free(line);
		return (false);
	}
	return (true);
}

void	cleanup(t_token *tokens, char *line)
{
	if (tokens)
		free_tokens(tokens);
	free(line);
}
