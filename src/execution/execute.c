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
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
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
static int	set_redirection_pipe(t_cmd *cmd, t_exec exec)
{
	int	fd_infile;
	int fd_outfile;

	if (exec.prev_pipe_read != -1)
	{
		dup2(exec.prev_pipe_read, STDIN_FILENO);
		close (exec.prev_pipe_read);
	}
	if (cmd->infile)
	{
		fd_infile = open (cmd->infile, O_RDONLY);
		if (fd_infile == -1)
		{
			fd_infile = open("/dev/null", O_RDONLY);
			if (fd_infile == -1)
				return (print_error("fallback failed"), 1); //is this not perror?
			else
				print_error("Warning: infile not found, using /dev/null\n"); //do I actually need to have this process? 
		}
		dup2(fd_infile, STDIN_FILENO);
		close (fd_infile);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			fd_outfile = open (cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_outfile = open (cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_outfile == -1)
			return (perror ("open"), 1);
		dup2 (fd_outfile, STDOUT_FILENO);
		close (fd_outfile);
	}
	if (cmd->next)
	{
		dup2 (exec.curr_pipe[1], STDOUT_FILENO);
		close (exec.curr_pipe[1]);
	}
	return (0);
}

static void	waitpid_loop(t_exec exec)
{
	int	i;
	
	i = 0;
	while (i < exec.num_pids)
	{
		waitpid (exec.pids[i], &exec.status, 0);
		i++;
	}
}

/* this is main function of executing the commands (and with args) */
int	execute(t_shell *shell)
{
	t_cmd	*curr;
	pid_t	pid;
	int		exit_code;
	
	curr = shell->commands;
	if (!curr->next && is_builtin(curr->argv) && !(curr->infile) && !(curr->outfile))
	{
		if (ft_strcmp(curr->argv[0], "exit") == 0)
			return (execute_builtin_exit(shell));
		return (execute_builtin(curr->argv, shell->envp));
	}
	shell->exec.num_pids = 0;
	shell->exec.prev_pipe_read = -1;
	while (curr)
	{
		if (curr->next && pipe(shell->exec.curr_pipe) == -1)
			return (perror("pipe failed"), 1);
		pid = fork();
		if (pid == 0)
		{
			if (set_redirection_pipe(curr, shell->exec) == 1)
			{
				cleanup_child(shell->exec);
				exit (1);
			}
			execute_command(curr->argv, shell->exec, shell);
		}
		else
		{
			shell->exec.pids[shell->exec.num_pids++] = pid;
			if (shell->exec.prev_pipe_read != -1)
				close (shell->exec.prev_pipe_read);
			if (curr->next)
			{
				shell->exec.prev_pipe_read = shell->exec.curr_pipe[0];
				close (shell->exec.curr_pipe[1]);
			}
		}
		curr = curr->next;
	}
	waitpid_loop(shell->exec);
	if (WIFEXITED(shell->exec.status))
		exit_code = WEXITSTATUS(shell->exec.status);
	else
		exit_code = 1;
	printf ("exit code at execution : %d\n", exit_code);
	return (exit_code);
}