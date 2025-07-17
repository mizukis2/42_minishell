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

int	execute (t_cmd *cmd, t_shell *shell)
{
	t_cmd *curr;
	
	curr = cmd;
	shell->last_exit_code = 0;
	while (curr)
	{
		if (curr->next)
			pipe_prcess();
		if (curr->infile)
			infile_process();
			//if (heredoc is true, run heredoc process)
		if (curr->outfile)
			outfile_process();
			if (curr->append == true)
				append_process();
		if (is_builtin(curr->argv[0]))
			execute_builtin(curr->argv, shell); // t_shell *shell stores the last_exit_code
		else
			external_external_cmd();
		curr = curr->next;
	}

	//this part need to be inside of the loop???
	close file discripters so far (the files opend during the loop above)
	waitpid (pid1, NULL, 0);
	waitpid (pid2, &status, 0);
	return (status);
}