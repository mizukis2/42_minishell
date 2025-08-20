/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   clean_exit.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/28 12:20:00 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/28 12:20:02 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_if_open(int *fd)
{
	if (*fd >= 0)
	{
		close (*fd);
		*fd = -1;
	}
}

void	restore_std_close_fd(int save_in, int save_out)
{
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		close (save_in);
	}
	if (save_out >= 0)
	{
		dup2(save_out, STDOUT_FILENO);
		close (save_out);
	}
}

void	free_split(char **split_list)
{
	int	i;

	if (!split_list)
		return ;
	i = 0;
	while (split_list[i])
	{
		free (split_list[i]);
		i++;
	}
	free(split_list);
}

void	cleanup_child(t_shell *shell)
{
	if (shell->exec.curr_pipe[0] >= 0)
		close (shell->exec.curr_pipe[0]);
	if (shell->exec.curr_pipe[1] >= 0)
		close (shell->exec.curr_pipe[1]);
	if (shell->exec.prev_pipe_read >= 0)
		close (shell->exec.prev_pipe_read);
}

void	clean_exit(t_shell *shell, const char *msg, char *cmd, int code)
{
	if (msg)
		print_error_builtin (msg);
	if (cmd)
		ft_putendl_fd(cmd, 2);
	cleanup_child(shell);
	if (shell->exec.curr_pipe[0] >= 0)
		close (shell->exec.curr_pipe[0]);
	if (shell->exec.curr_pipe[1] >= 0)
		close (shell->exec.curr_pipe[1]);
	if (shell->line)
		free(shell->line);
	if (shell->commands)
		free_cmd_list(shell->commands);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->env_list)
		free_node_list(shell->env_list);
	exit (code);
}
