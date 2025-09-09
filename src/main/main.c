/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:48:11 by zekhatib          #+#    #+#             */
/*   Updated: 2025/09/09 20:27:32 by zekhatib         ###   ########.fr       */
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
	if (!envp || !*envp || !**envp)
		return (0);
	if (ac != 1)
	{
		printf("\e[0;31mError: No arguments needed\e[0m\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (!args_check(ac, envp))
		return (EXIT_FAILURE);
	print_banner();
	start_shell(envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
