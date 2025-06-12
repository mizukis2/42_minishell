/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:48:11 by zekhatib          #+#    #+#             */
/*   Updated: 2025/06/11 07:57:51 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char *line;

	if (ac != 1)
		return (ft_printf(ERROR_ARG), 1);
	if (!av || !*av || !**av || !envp || !*envp|| !**envp)
		return (1);

	//Copy environment variables into a modifiable structure
	
	/*
	this infinite loop like this or implemet loop with signals?
	 */
	while (1) // while the signal is 
	{
		line = readline("MINISHELL >> ");
		//if Ctrl+D or type "exit"
		//if no line or Ctrl+c = show prompt
		//if there is line
		add_history (line);
		//lexer & parse
		//execution
		free (line); //I think we need to have "cleaning function" later
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
