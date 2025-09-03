/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   set_redir_utils.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/27 14:10:53 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/27 14:10:54 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	infile_process(const t_redir *r)
{
	int	fd_in;

	fd_in = open (r->target, O_RDONLY);
	if (fd_in == -1)
	{
		perror(r->target);
		return (false);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close (fd_in);
		perror ("dup2");
		return (false);
	}
	close (fd_in);
	if (r->type == R_HEREDOC)
		unlink(r->target);
	return (true);
}

bool	outfile_process(t_redir *r)
{
	int	fd_out;

	if (r->type == R_APPEND)
		fd_out = open (r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open (r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (perror (r->target), false);
	if (dup2 (fd_out, STDOUT_FILENO) == -1)
	{
		close (fd_out);
		return (false);
	}
	close (fd_out);
	return (true);
}
