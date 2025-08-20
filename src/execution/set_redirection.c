/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   set_redirection.c                                   :+:    :+:           */
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

static bool	hook_prev_pipe_stdin(t_exec *exec)
{
	if (exec->prev_pipe_read < 0)
		return (true);
	if (dup2(exec->prev_pipe_read, STDIN_FILENO) == -1)
	{
		perror ("dup2 prev_pipe_read");
		close (exec->prev_pipe_read);
		return (false);
	}
	close_fd_if_open (&exec->prev_pipe_read);
	return (true);
}

static bool	apply_redirections(t_redir *redirs, bool *out_redir_seen)
{
	t_redir	*r;

	r = redirs;
	*out_redir_seen = false;
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
			*out_redir_seen = true;
		}
		r = r->next;
	}
	return (true);
}

static bool	hook_next_pipe_stdout(t_exec *exec, bool out_redir_seen)
{
	close_fd_if_open(&exec->curr_pipe[0]);
	if (out_redir_seen)
		return (true);
	if (exec->curr_pipe[1] < 0)
		return (false);
	if (dup2 (exec->curr_pipe[1], STDOUT_FILENO) == -1)
	{
		perror ("dup2 curr_pipe[1]");
		close_fd_if_open (&exec->curr_pipe[1]);
		return (false);
	}
	close_fd_if_open(&exec->curr_pipe[1]);
	return (true);
}

bool	set_redirection_pipe(t_cmd *curr_cmd, t_exec *exec)
{
	bool	out_redir_seen;

	if (!hook_prev_pipe_stdin(exec))
		return (false);
	if (!apply_redirections(curr_cmd->redirs, &out_redir_seen))
		return (false);
	if (curr_cmd->next)
	{
		if (!hook_next_pipe_stdout(exec, out_redir_seen))
			return (false);
	}
	else
	{
		close_fd_if_open(&exec->curr_pipe[0]);
		close_fd_if_open(&exec->curr_pipe[1]);
	}
	return (true);
}
