/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   cleaning.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 13:14:32 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 13:14:34 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this is just an idea, we will update later


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

/* void	clean_exit(t_fds *fds, const char *msg, int code)
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
 */
