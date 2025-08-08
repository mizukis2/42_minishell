/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execute_utils.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/06 14:48:17 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/06 14:48:19 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **argv)
{
	static const char	*builtins[] = {"echo", "cd",
		"pwd", "export", "unset", "env", "exit", NULL};
	int					i;

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
	static const char	*builtins_parent[] = {"cd",
		"export", "unset", "exit", NULL};
	int					i;

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

void	init_exec(t_exec *exec)
{
	exec->prev_pipe_read = -1;
	exec->curr_pipe[0] = -1;
	exec->curr_pipe[1] = -1;
	exec->num_pids = 0;
	exec->last_pid = -1;
	exec->status = 0;
}

void	waitpid_loop(t_exec *exec)
{
	int	i;
	int	status;

	i = 0;
	while (i < exec->num_pids)
	{
		waitpid (exec->pids[i], &status, 0);
		if (i == exec->num_pids - 1)
			exec->status = status;
		i++;
	}
}

/* this is a function to run builtin in parent. this returns the exit code*/
int	run_builtin_parent(t_cmd *curr_cmd, t_shell *shell)
{
	int	save_in;
	int	save_out;
	int	result;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (!set_redirection_pipe(curr_cmd, &shell->exec))
	{
		perror("set_redirection_pipe failed(parent:builtin)");
		close (save_in);
		close (save_out);
		return (1);
	}
	if (ft_strcmp(curr_cmd->argv[0], "exit") == 0)
		return (execute_builtin_exit(shell, save_in, save_out));
	result = execute_builtin(curr_cmd->argv, shell->env_list);
	restore_std_close_fd(save_in, save_out);
	return (result);
}
