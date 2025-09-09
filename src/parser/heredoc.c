/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:45:45 by zekhatib          #+#    #+#             */
/*   Updated: 2025/09/09 06:22:17 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expect_delim_no_expand(t_token **tok_it, t_shell *shell,
										t_cmd *cmd)
{
	char	*str;

	if (!tok_it || !*tok_it || (*tok_it)->type != TOKEN_WORD)
	{
		set_invalid(cmd, shell, 2);
		return (NULL);
	}
	str = ft_strdup((*tok_it)->value);
	if (!str)
	{
		set_invalid(cmd, shell, 1);
		return (NULL);
	}
	*tok_it = (*tok_it)->next;
	return (str);
}

void	handle_heredoc_redir(t_token **tok_it, t_cmd *cmd, t_shell *shell)
{
	char	*delim;
	char	*path;

	delim = expect_delim_no_expand(tok_it, shell, cmd);
	if (!delim)
		return ;
	path = create_heredoc_file(delim, shell);
	free(delim);
	if (!path)
	{
		if (g_signal == SIGINT)
		{
			cmd->invalid = true;
			return ;
		}
		return (set_invalid(cmd, shell, 1));
	}
	if (!add_redir(&cmd->redirs, R_HEREDOC, path, true))
	{
		free(path);
		return (set_invalid(cmd, shell, 1));
	}
	free(path);
}

static void	run_heredoc_child(t_heredoc *heredoc, t_shell *shell)
{
	set_signals_heredoc_child();
	collect_hd(heredoc->fd, heredoc->clean_delim,
		heredoc->is_quoted, shell);
	free(heredoc->clean_delim);
	close(heredoc->fd);
	_exit(0);
}

static char	*handle_heredoc_parent(t_heredoc *heredoc,
									t_shell *shell, int status)
{
	close(heredoc->fd);
	set_signals_prompt();
	free(heredoc->clean_delim);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(heredoc->temp_path);
		free(heredoc->temp_path);
		shell->last_exit_code = 130;
		g_signal = SIGINT;
		cleanup(shell);
		return (NULL);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(heredoc->temp_path);
		free(heredoc->temp_path);
		return (NULL);
	}
	return (heredoc->temp_path);
}

char	*create_heredoc_file(const char *delim, t_shell *shell)
{
	t_heredoc	heredoc;
	bool		quoted;
	pid_t		pid;
	int			status;

	heredoc.clean_delim = strip_delim_quotes(delim, &quoted);
	heredoc.is_quoted = quoted;
	if (!heredoc.clean_delim)
		return (NULL);
	heredoc.fd = create_temp_heredoc(&heredoc.temp_path);
	if (heredoc.fd < 0)
		return (free(heredoc.clean_delim), NULL);
	pid = fork();
	if (pid < 0)
		return (close(heredoc.fd), free(heredoc.clean_delim),
			free(heredoc.temp_path), NULL);
	if (pid == 0)
		run_heredoc_child(&heredoc, shell);
	set_signals_heredoc_parent();
	waitpid(pid, &status, 0);
	return (handle_heredoc_parent(&heredoc, shell, status));
}
