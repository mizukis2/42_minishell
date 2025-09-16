/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:51:29 by zekhatib          #+#    #+#             */
/*   Updated: 2025/07/31 05:17:54 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty(char *str)
{
	if (str == NULL)
		return (1);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
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

bool	is_valid_input(t_shell *shell)
{
	if (shell->line == NULL)
	{
		shell->last_exit_code = 0;
		return (false);
	}
	if (is_empty(shell->line))
	{
		free(shell->line);
		shell->line = NULL;
		shell->last_exit_code = 0;
		return (false);
	}
	if (!check_quotes(shell->line))
	{
		print_error("SYNTAX ERROR - Unclosed Quotes");
		free(shell->line);
		shell->line = NULL;
		shell->last_exit_code = 258;
		return (false);
	}
	return (true);
}

void	cleanup(t_shell *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->commands)
	{
		free_cmd_list(shell->commands);
		shell->commands = NULL;
	}
}
