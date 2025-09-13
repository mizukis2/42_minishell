/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:22:17 by mmatsui           #+#    #+#             */
/*   Updated: 2025/09/13 01:53:46 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this runs as child process */
static void	run_exec_child(t_cmd *curr_cmd, t_shell *shell)
{
	set_signals_child();
	if (!set_redirection_pipe(curr_cmd, &shell->exec))
	{
		cleanup_child(shell);
		exit(1);
	}
	if (!curr_cmd->argv || !curr_cmd->argv[0])
	{
		cleanup_child(shell);
		exit (0);
	}
	execute_command(curr_cmd->argv, shell);
	exit (127);
}

static void	run_exec_parent(t_cmd *curr_cmd, t_shell *shell, pid_t pid)
{
	shell->exec.pids[shell->exec.num_pids++] = pid;
	if (shell->exec.prev_pipe_read != -1)
	{
		close (shell->exec.prev_pipe_read);
		shell->exec.prev_pipe_read = -1;
	}
	if (curr_cmd->next)
	{
		shell->exec.prev_pipe_read = shell->exec.curr_pipe[0];
		close (shell->exec.curr_pipe[1]);
		shell->exec.curr_pipe[1] = -1;
	}
	else
	{
		if (shell->exec.curr_pipe[0] != -1)
		{
			close (shell->exec.curr_pipe[0]);
			shell->exec.curr_pipe[0] = -1;
		}
		if (shell->exec.curr_pipe[1] != -1)
		{
			close (shell->exec.curr_pipe[1]);
			shell->exec.curr_pipe[1] = -1;
		}
	}
}

static int	run_child_or_parent(t_cmd *curr, t_shell *shell, pid_t pid)
{
	if (pid == 0)
		run_exec_child(curr, shell);
	else if (pid > 0)
		run_exec_parent(curr, shell, pid);
	else
	{
		cleanup_child(shell);
		print_error_errno("fork", errno);
		return (1);
	}
	return (0);
}

/* this is main function of executing the commands (and with args)
this runs in parent. return with the exit code */
int	execute(t_shell *shell)
{
	t_cmd	*curr;
	pid_t	pid;
	int		exit_code;

	curr = shell->commands;
	exit_code = -1;
	if (!curr->next)
	{
		exit_code = guard_single_command(curr, shell);
		if (exit_code >= 0)
			return (exit_code);
	}
	init_exec(&shell->exec);
	set_signals_parent();
	while (curr)
	{
		if (curr->next && pipe(shell->exec.curr_pipe) == -1)
			return (print_error_errno("pipe", errno), 1);
		pid = fork();
		if (run_child_or_parent (curr, shell, pid) != 0)
			return (1);
		curr = curr->next;
	}
	waitpid_loop(&shell->exec);
	return (find_exit_code(shell));
}

void	run_execution(t_shell *shell)
{
	shell->last_exit_code = execute(shell);
}
