/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 08:46:16 by mmatsui        #+#    #+#                */
/*   Updated: 2025/05/22 14:22:32 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_cmd(t_fds *fds, t_cmd *cmd, char **envp)
{
	if (!cmd->run_cmd || cmd->run_cmd[0] == '\0')
		free_clean_exit(cmd->args, fds, "Command not found", 127);
	cmd->args = ft_split(cmd->run_cmd, ' ');
	if (!cmd->args)
		clean_exit(fds, "split args failed", 1);
	cmd->cmd_name = cmd->args[0];
	cmd->path = find_path(cmd, envp);
	if (!cmd->path)
		free_clean_exit(cmd->args, fds, "Command not found", 127);
	execve(cmd->path, cmd->args, envp);
	free(cmd->path);
	ft_free_split(cmd->args);
	perror ("execve failed");
	exit (127);
}

static void	child_cmd2(t_fds *fds, t_cmd *cmd, char **envp)
{
	if (dup2 (fds->pipe_read, STDIN_FILENO) < 0)
		clean_exit(fds, "dup2 infile_fd failed", 1);
	if (dup2 (fds->outfile, STDOUT_FILENO) < 0)
		clean_exit(fds, "dup2 pipefd[1] failed", 1);
	close (fds->outfile);
	close (fds->pipe_read);
	close (fds->pipe_write);
	execute_cmd(fds, cmd, envp);
}

static void	child_cmd1(t_fds *fds, t_cmd *cmd, char **envp)
{
	if (dup2 (fds->infile, STDIN_FILENO) < 0)
		clean_exit(fds, "dup2 infile_fd failed", 1);
	if (dup2 (fds->pipe_write, STDOUT_FILENO) < 0)
		clean_exit(fds, "dup2 pipefd[1] failed", 1);
	close (fds->infile);
	close (fds->pipe_read);
	close (fds->pipe_write);
	execute_cmd(fds, cmd, envp);
}

int	pipex(int *pipefd, t_fds *fds, t_cmd *cmd, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) < 0)
		clean_exit(fds, "Error related to pipe", 1);
	fds->pipe_read = pipefd[0];
	fds->pipe_write = pipefd[1];
	cmd->run_cmd = cmd->cmd1;
	pid1 = fork ();
	if (pid1 == 0)
		child_cmd1(fds, cmd, envp);
	else if (pid1 < 0)
		clean_exit(fds, "fork1 failed", 1);
	cmd->run_cmd = cmd->cmd2;
	pid2 = fork ();
	if (pid2 == 0)
		child_cmd2(fds, cmd, envp);
	else if (pid2 < 0)
		clean_exit(fds, "fork2 failed", 1);
	close (pipefd[0]);
	close (pipefd[1]);
	waitpid (pid1, NULL, 0);
	waitpid (pid2, &status, 0);
	return (status);
}
