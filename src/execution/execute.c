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

	if (exec->prev_pipe_read != -1)
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
		dup2 (exec->curr_pipe[1], STDOUT_FILENO);
		close (exec->curr_pipe[1]);
	}
	return (0);
}

static void	waitpid_loop(t_exec *exec)
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
	t_cmd	*curr;
	t_exec	*exec;
	pid_t	pid;
	int		exit_code;
	
	curr = cmd;
	if (!curr->next && is_builtin(curr->argv) && !(curr->infile) && !(curr->outfile))
		return (execute_builtin(curr->argv, shell->envp));
	//until here, there is no fd, malloc to cleanup
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (perror("execute: malloc"), 1);
	//this malloc, we clean up in the end of the code (parent)
	exec->num_pids = 0; //init
	exec->prev_pipe_read = -1; //init
	while (curr)
	{
		if (curr->next && pipe(exec->curr_pipe) == -1)
			return (perror("pipe failed"), 1);
		//after this we need to cleanup pipe (curr_pipe[0],curr_pipe[1] )
		pid = fork();
		if (pid == 0)
		{
			//this is now inside of the child process
			if (set_redirection_pipe(curr, exec) == 1)
			{
				cleanup_child(exec);
				exit (1);
			}
			execute_command(curr->argv, exec, shell);
		}
		else
		{
			//this is parent process
			exec->pids[exec->num_pids++] = pid;
			if (exec->prev_pipe_read != -1)
				close (exec->prev_pipe_read);
			if (curr->next)
			{
				exec->prev_pipe_read = exec->curr_pipe[0];
				close (exec->curr_pipe[1]);
			}
		}
		curr = curr->next;
	}
	waitpid_loop(exec);
	if WEXITSTATUS(exec->status)
		exit_code = WEXITSTATUS(exec->status);
	else
		exit_code = 1;
	free (exec);
	return (exit_code);
}