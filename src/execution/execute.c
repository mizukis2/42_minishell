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

bool	is_builtin(char *cmd)
{
	static const char *builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};
	int	i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool is_safe_to_run_in_child(char *cmd)
{
	static const char *builtins_in_child[] = {
		"echo", "pwd","env", NULL
	};
	int	i;
	while (builtins_in_child[i])
	{
		if (ft_strcmp(cmd, builtins_in_child[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	execute(t_cmd *cmd, t_exec *exec, t_shell *shell)
{
	t_cmd *curr;
	pid_t pid; 
	
	curr = cmd;
	shell->last_exit_code = 0;
	if (!curr->next && is_builtin(curr->argv) && !(curr->infile) && !(curr->outfile))
		shell->last_exit_code = execute_builtin(curr->argv, shell->envp);
	while (curr)
	{
		if (curr->next)
			pipe(exec->curr_pipe);
		pid = fork();
		if (pid == 0)
		{
			if (!set_redirection_pipe(exec))
				exit (clean_exit());
			close_unuse_files();
			execute_command();
		}
		else 
		{
			close_unuse_files();
			save_pid();
			//update prev_pipe = curr_pipe
		}
		curr = curr->next;
	}
	//this waitpid should loop
	//waitpid (exec->last_pid, exec->status, 0);
	//update shell->last_exit_code
}