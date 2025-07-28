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

/* child process */
static int	set_redirection_pipe(t_cmd *cmd, t_exec *exec)
{
	int	fd_infile;
	int fd_outfile;

	if (exec->prev_pipe[0] != -1)
		dup2(exec->prev_pipe[0], STDIN_FILENO);
	if (cmd->infile)
	{
		fd_infile = open (cmd->infile, O_RDONLY);
		if (fd_infile == -1)
		{
			cmd->infile = open("/dev/null", O_RDONLY);
			if (cmd->infile == -1)
				return (print_error("fallback failed"), 1);
		}
			return (perror("open"), 1);
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
		dup2 (exec->curr_pipe[1], STDOUT_FILENO);
	return (0);
}

void	waitpid_loop(t_exec *exec)
{
	int	i;
	
	i = 0;
	while (i < exec->num_pids)
	{
		waitpid (exec->pids[i], &exec->status, 0);
		i++;
	}
}

/* this is main function of executing the commands (and with args) */
int	execute(t_cmd *cmd, t_shell *shell)
{
	t_exec	*exec;
	t_cmd	*curr;
	pid_t	pid;
	int		exit_code;
	
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (perror("malloc failed"), 1); //do I need to perror when malloc failed?
	exec->num_pids = 0;
	curr = cmd;
	if (!curr->next && is_builtin(curr->argv) && !(curr->infile) && !(curr->outfile))
		return (execute_builtin(curr->argv, shell->envp));
	while (curr)
	{
		if (curr->next)
			pipe(exec->curr_pipe);
		pid = fork();
		if (pid == 0)
		{
			if (!set_redirection_pipe(curr, exec))
			{
				cleanup_child(exec);
				exit (1);
			}
			close (exec->curr_pipe[1]);
			execute_command(curr->argv, exec, shell);
		}
		else
		{
			exec->pids[exec->num_pids++] = pid;
			exec->prev_pipe[0] = exec->curr_pipe[0];
			close (exec->curr_pipe[0]);
		}
		curr = curr->next;
	}
	waitpid_loop(exec);
	exit_code = exec->status;
	free (exec);
	return (exit_code);
}