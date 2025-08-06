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
}

void	clean_exit(t_shell *shell, const char *msg, char *cmd, int code)
{
	printf ("here clean_exit\n");
	if (msg)
		print_error (msg);
	if (cmd)
		ft_putendl_fd(cmd, 2);
	cleanup_child(shell);
	printf("exit code:%d\n", code);
	if (shell->line)
		free(shell->line);
	if (shell->commands)
		free_cmd_list(shell->commands);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->env_list)
		free_node_list(shell->env_list);
	free (shell);
	exit (code);
}

