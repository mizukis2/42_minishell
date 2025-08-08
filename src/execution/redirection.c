/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   redirection.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/06 14:50:58 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/06 14:51:00 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	infile_process(t_cmd *cmd)
{
	int	fd_infile;

	fd_infile = open (cmd->infile, O_RDONLY);
	if (fd_infile == -1)
	{
		print_error_builtin(cmd->infile);
		print_error_builtin(": ");
		return (false);
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		close (fd_infile);
		return (false);
	}
	close (fd_infile);
	return (true);
}

static bool	outfile_process(t_cmd *cmd)
{
	int	fd_outfile;

	if (cmd->append)
		fd_outfile = open (cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_outfile = open (cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		return (perror ("open"), false);
	if (dup2 (fd_outfile, STDOUT_FILENO) == -1)
	{
		close (fd_outfile);
		return (false);
	}
	close (fd_outfile);
	return (true);
}

bool	set_redirection_pipe(t_cmd *curr_cmd, t_exec *exec)
{
	if (exec->prev_pipe_read >= 0)
	{
		if (dup2(exec->prev_pipe_read, STDIN_FILENO) == -1)
			return (false);
		close (exec->prev_pipe_read);
		exec->prev_pipe_read = -1;
	}
	if (curr_cmd->infile && !(infile_process(curr_cmd)))
		return (false);
	if (curr_cmd->outfile)
	{
		if (!outfile_process(curr_cmd))
			return (false);
	}
	else if (curr_cmd->next)
	{
		if (dup2 (exec->curr_pipe[1], STDOUT_FILENO) == -1)
		{
			close (exec->curr_pipe[1]);
			return (false);
		}
		close (exec->curr_pipe[1]);
	}
	return (true);
}
