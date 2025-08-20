/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   run_execution.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 13:22:17 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 13:22:18 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
} */

/* this runs as child process */
static void	run_exec_child(t_cmd *curr_cmd, t_shell *shell)
{
	//signal_child();
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

static int	find_exit_code(t_shell *shell)
{
	if (WIFEXITED(shell->exec.status))
		return (WEXITSTATUS(shell->exec.status));
	else if (WIFSIGNALED(shell->exec.status))
		return (128 + WTERMSIG(shell->exec.status));
	return (1);
}

static int	guard_single_command(t_cmd *curr, t_shell *shell)
{
	if (!curr->argv || !curr->argv[0])
		return (0);
	if (is_builtin(curr->argv))
		return (run_builtin_parent(curr, shell));
	return (-1);
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
	while (curr)
	{
		if (curr->next && pipe(shell->exec.curr_pipe) == -1)
			return (perror("pipe failed"), 1);
		pid = fork();
		if (pid == 0)
			run_exec_child(curr, shell);
		else
			run_exec_parent(curr, shell, pid);
		curr = curr->next;
	}
	waitpid_loop(&shell->exec);
	return (find_exit_code(shell));
}

void	run_execution(t_shell *shell)
{
	shell->last_exit_code = execute(shell);
}
