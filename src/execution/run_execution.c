/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   run_execute.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 13:22:17 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 13:22:18 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_exec_child(t_cmd *commands, t_shell *shell)
{
	if (!set_redirection_pipe(commands, &shell->exec))
	{
		perror("set_redirection_pipe failed");
		clean_exit(shell, NULL, NULL, 1);
	}
	execute_command(commands->argv, shell);
}

static void	run_exec_parent(t_cmd *commands, t_shell *shell, pid_t pid)
{
	shell->exec.pids[shell->exec.num_pids++] = pid;
	if (shell->exec.prev_pipe_read != -1)
		close (shell->exec.prev_pipe_read);
	if (commands->next)
	{
		shell->exec.prev_pipe_read = shell->exec.curr_pipe[0];
		close (shell->exec.curr_pipe[1]);
	}
}

static int	find_exit_code(t_shell *shell)
{
	if (WIFEXITED(shell->exec.status))
		return (WEXITSTATUS(shell->exec.status));
	//add else if signal thisng here
/* 	else if (WIFSIGNALED(shell->exec.status))
		return (128 + WTERMSIG(shell->exec.status)); */
	return (1);
}

/* this is main function of executing the commands (and with args) */
int	execute(t_shell *shell)
{
	t_cmd	*curr;
	pid_t	pid;
	int		exit_code;

	curr = shell->commands;
	exit_code = 1;
	if (!curr->next && is_builtin(curr->argv))
		return (run_builtin_parent(curr, shell));
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
