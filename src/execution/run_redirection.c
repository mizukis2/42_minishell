/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   run_redirection.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/06 14:50:58 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/06 14:51:00 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	infile_process(const t_redir *r)
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
		return (false);
	}
	close (fd_in);
	if (r->type == R_HEREDOC)
		unlink(r->target);
	return (true);
}

static bool	outfile_process(t_redir *r)
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

bool	run_redirection_pipe(t_cmd *curr_cmd, t_exec *exec) //name change
{
	bool out_redir_seen;
	t_redir *r;
	
	out_redir_seen = false;
	if (exec->prev_pipe_read >= 0)
	{
		if (dup2(exec->prev_pipe_read, STDIN_FILENO) == -1)
		{
			perror ("dup2 prev_pipe_read");
			close (exec->prev_pipe_read);
			return (false);
		}
		close (exec->prev_pipe_read);
		exec->prev_pipe_read = -1;
	}
	r = curr_cmd->redirs;
	while (r)
	{
		if (r->type == R_IN || r->type == R_HEREDOC)
		{
			if (!(infile_process(r)))
				return (false);
		}
		else
		{
			if (!(outfile_process(r)))
		 		return (false);
			out_redir_seen = true;
		}
		r = r->next;
	}
	if (curr_cmd->next)
	{
		if (exec->curr_pipe[0] >= 0)
		{
			close (exec->curr_pipe[0]);
			exec->curr_pipe[0] = -1;
		}
		if (!out_redir_seen)
		{
			if (exec->curr_pipe[1] < 0)
				return (false);
			if (dup2 (exec->curr_pipe[1], STDOUT_FILENO) == -1)
			{
				perror ("dup2 curr_pipe[1]");
				close (exec->curr_pipe[1]);
				exec->curr_pipe[1] = -1;
				return (false);
			}
		}
		if (exec->curr_pipe[1] >= 0)
		{
			close (exec->curr_pipe[1]);
			exec->curr_pipe[1] = -1;
		}
		else {
			if (exec->curr_pipe[0] >= 0)
			{
				close (exec->curr_pipe[1]);
				exec->curr_pipe[0] = -1;
			}
			if (exec->curr_pipe[1] >= 0)
			{
				close (exec->curr_pipe[1]);
				exec->curr_pipe[1] = -1;
			}
		}
	}
	return (true);
}
