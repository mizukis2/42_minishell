/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:51:29 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/09 14:40:04 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_empty(char *line)
{
	return (line[0] == '\0');
}

static bool	check_quotes(char *line)
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
	if (is_empty(line))
		return (false);
	if (!check_quotes(line))
	{
		printf("\e[0;31mSyntax error: Unclosed Quotes\e[0m\n");
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
