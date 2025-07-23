/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   init_exit_cleaning.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/21 13:49:59 by mmatsui        #+#    #+#                */
/*   Updated: 2025/05/22 14:00:55 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **split_list)
{
	int	i;

	if (!split_list)
		return ;
	i = 0;
	while (split_list[i])
	{
		free (split_list[i]);
		i++;
	}
	free(split_list);
}

void	clean_exit(t_fds *fds, const char *msg, int code)
{
	if (fds->infile >= 0)
		close (fds->infile);
	if (fds->outfile >= 0)
		close (fds->outfile);
	if (fds->pipe_read >= 0)
		close (fds->pipe_read);
	if (fds->pipe_write >= 0)
		close (fds->pipe_write);
	if (msg)
		perror (msg);
	exit(code);
}

void	free_clean_exit(char **split_list,
	t_fds *fds, const char *msg, int code)
{
	if (split_list)
		ft_free_split(split_list);
	clean_exit(fds, msg, code);
}

void	init_variable(t_fds *fds, t_cmd *cmd, char **av)
{
	fds->infile = -1;
	fds->outfile = -1;
	fds->pipe_read = -1;
	fds->pipe_write = -1;
	cmd->cmd1 = av[2];
	cmd->cmd2 = av[3];
	cmd->run_cmd = NULL;
	cmd->cmd_name = NULL;
	cmd->path = NULL;
	cmd->args = NULL;
}
