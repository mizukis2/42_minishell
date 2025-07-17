/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/22 13:37:40 by mmatsui        #+#    #+#                */
/*   Updated: 2025/05/22 14:23:22 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	t_fds	fds;
	t_cmd	cmd;
	int		status;

	if (ac != 5)
		return (ft_printf (ERROR_ARG), 1);
	init_variable(&fds, &cmd, av);
	open_in_out_file(&fds, av);
	status = pipex(pipefd, &fds, &cmd, envp);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
