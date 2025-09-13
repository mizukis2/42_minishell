/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:02:03 by mmatsui           #+#    #+#             */
/*   Updated: 2025/09/13 01:50:27 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_exit_code(t_shell *shell)
{
	int	sig;

	if (WIFEXITED(shell->exec.status))
		return (WEXITSTATUS(shell->exec.status));
	else if (WIFSIGNALED(shell->exec.status))
	{
		sig = WTERMSIG(shell->exec.status);
		if (sig == SIGQUIT)
		{
			write(STDERR_FILENO, "\nQuit (core dumped)\n", 20);
			return (128 + sig);
		}
		return (128 + sig);
	}
	return (1);
}

int	guard_single_command(t_cmd *curr, t_shell *shell)
{
	if (!curr->argv || !curr->argv[0])
		return (0);
	if (is_builtin(curr->argv))
		return (run_builtin_parent(curr, shell));
	return (-1);
}

void	init_exec(t_exec *exec)
{
	exec->prev_pipe_read = -1;
	exec->curr_pipe[0] = -1;
	exec->curr_pipe[1] = -1;
	exec->num_pids = 0;
	exec->last_pid = -1;
	exec->status = 0;
}
