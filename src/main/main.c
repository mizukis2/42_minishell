/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:48:11 by zekhatib          #+#    #+#             */
/*   Updated: 2025/06/30 05:04:54 by zekhatib         ###   ########.fr       */
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

static int	args_check(int ac, char **envp)
{
	if (ac != 1 || !envp || !*envp || !**envp)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (!args_check(ac, envp))
		return (EXIT_FAILURE);
	print_banner();
	enter_shell_loop();
	cleanup_shell();
	return (EXIT_SUCCESS);
}
	//TODO: Copy environment variables into a modifiable structure
	//TODO: Add parsing, execution
	//TODO: Add signal handling at the end of the project