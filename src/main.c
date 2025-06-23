/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:48:11 by zekhatib          #+#    #+#             */
/*   Updated: 2025/06/23 03:27:26 by zekhatib         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char *line;

	(void)ac;
	(void)av;
	if (ac != 1 || !envp || !*envp|| !**envp)//sanity check for environment variables
		return (1);
	//TODO: Copy environment variables into a modifiable structure
	print_banner();
	while (1)
	{
		line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (!line) //for Ctrl+D on an empty line
		{
			printf("\033[0;31mexited MZ$HELL\033[0m\n");
			break;
		}
		if (ft_strncmp(line, "exit", 4) == 0)//exit command
		{
			free(line);
			printf("\033[0;31mexited MZ$HELL\033[0m\n");
			break;
		}
		if (!*line) //ignore empty lines
		{
			free(line);
			continue;
		}
		add_history (line);
		//TODO: Add parsing, execution and signal handling here
		free (line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
