/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execute.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 13:22:17 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 13:22:18 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **argv)
{
	static const char *builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};
	int	i;

	i = 0;
	if (!argv || !argv[0])
		return (false);
	while (builtins[i])
	{
		if (ft_strcmp(argv[0], builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	run_in_parent(char **argv)
{
	static const char *builtins_parent[] = {
		"cd", "export", "unset", "exit", NULL
	};
	int	i;

	i = 0;
	if (!argv || !argv[0])
		return (false);
	while (builtins_parent[i])
	{
		if (ft_strcmp(argv[0], builtins_parent[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

/* child process */
static bool	set_redirection_pipe(t_cmd *cmd, t_exec *exec)
{
	int	fd_infile;
	int fd_outfile;
	if (!cmd->infile && !cmd->outfile)
		return (true);
	if (exec->prev_pipe_read >= 0)
	{
		dup2(exec->prev_pipe_read, STDIN_FILENO);
		close (exec->prev_pipe_read);
	}
	if (cmd->infile)
	{
		fd_infile = open (cmd->infile, O_RDONLY);
		if (fd_infile == -1)
		{
 			fd_infile = open("/dev/null", O_RDONLY);
			if (fd_infile == -1)
				return (print_error("fallback failed"), false); //is this not perror?
			else
				print_error("Warning: infile not found, using /dev/null\n"); //do I actually need to have this process?
		}
		dup2(fd_infile, STDIN_FILENO);
		close (fd_infile);
	}
	if (cmd->outfile)
	{
		printf ("outfile\n");
		if (cmd->append)
			fd_outfile = open (cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_outfile = open (cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_outfile == -1)
			return (perror ("open"), false);
		dup2 (fd_outfile, STDOUT_FILENO);
		close (fd_outfile);
	}
	if (!cmd->outfile && cmd->next)
	{
		dup2 (exec->curr_pipe[1], STDOUT_FILENO);
		close (exec->curr_pipe[1]);
	}
	return (true);
}

static void	waitpid_loop(t_exec *exec)
{
	int	i;
	int status;
	
	i = 0;
	while (i < exec->num_pids)
	{
		waitpid (exec->pids[i], &status, 0);
		if (i == exec->num_pids - 1)
			exec->status = status;
		i++;
	}
}

void init_exec(t_exec *exec)
{
	exec->prev_pipe_read = -1;
	exec->curr_pipe[0] = -1;
	exec->curr_pipe[1] = -1;
	exec->num_pids = 0;
	exec->last_pid = -1;
	exec->status = 0;
}

int	run_builtin_parent(t_cmd *commands, t_shell *shell)
{
	int	save_in;
	int save_out;
	int result;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (!set_redirection_pipe(commands, &shell->exec))
	{
		perror("set_redirection_pipe failed");
		close (save_in);
		close (save_out);
		return (1);
	}
	if (ft_strcmp(commands->argv[0], "exit") == 0)
		return (execute_builtin_exit(shell, save_in, save_out));
	result = execute_builtin(commands->argv, shell->env_list);
	close_restore_std(save_in, save_out);
	return (result);
}

void run_exec_child (t_cmd *commands,t_shell *shell)
{
	printf ("child process\n");
	if (!set_redirection_pipe(commands, &shell->exec))
			{
				perror("set_redirection_pipe failed");
				cleanup_child(shell);
				exit (1);
			}
			execute_command(commands->argv, shell);
}

void run_exec_parent(t_cmd *commands,t_shell *shell, pid_t pid)
{
	printf ("parent process\n");
	shell->exec.pids[shell->exec.num_pids++] = pid;
	if (shell->exec.prev_pipe_read != -1)
		close (shell->exec.prev_pipe_read);
	if (commands->next)
	{
		shell->exec.prev_pipe_read = shell->exec.curr_pipe[0];
		close (shell->exec.curr_pipe[1]);
	}

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
	if (WIFEXITED(shell->exec.status))
		exit_code = WEXITSTATUS(shell->exec.status);
	else
		exit_code = 1;
	printf ("exit code at execution : %d\n", exit_code);
	return (exit_code);
}

bool run_execution(t_shell *shell)
{
	shell->last_exit_code = execute(shell);
	return (true);
}
