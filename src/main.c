/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:48:11 by zekhatib          #+#    #+#             */
/*   Updated: 2025/06/24 05:51:53 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_banner(void)
{
	printf("\033[2J\033[H");
	printf("\033[38;2;0;255;127m");
	printf("███╗   ███╗███████╗▄▄███▄▄·██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║╚══███╔╝██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║  ███╔╝ ███████╗███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║ ███╔╝  ╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║███████╗███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚══════╝╚═▀▀▀══╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\033[1m\033[38;2;160;32;240m--- Made by mmatsui & zekhatib ---\n");
	printf("\033[0m\n");
}

static int	is_whitespace_or_empty(char *str)
{
	int i;

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

static bool	check_quotes(char *line)
{
	bool	in_quotes;
	char	quote;
	int		i;
	
	in_quotes = false;
	quote = 0;
	i = 0;
	while(line[i])
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

int	main(int ac, char **av, char **envp)
{
	char *line;

	(void)av;
	if (ac != 1 || !envp || !*envp|| !**envp)
		return (EXIT_FAILURE);
	print_banner();
	while (1)
	{
		line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");

		if (!line) // check for EOF Ctrl+D (temporary)
			break;
		if (is_whitespace_or_empty(line))
		{
			free(line);
			continue;
		}
		add_history (line);
		if (!check_quotes(line))
		{
			printf("Syntax error: Unclosed Quotes\n");
			free(line);
			continue;
		}
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
	//TODO: Copy environment variables into a modifiable structure
	//TODO: Add parsing, execution
	//TODO: Add signal handling at the end of the project