/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser_free_clean.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/15 13:37:23 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/15 13:37:24 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirs(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		if (r->is_heredoc && r->target)
			unlink(r->target);
		free(r->target);
		free(r);
		r = next;
	}
}

void free_single_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return;
	i = 0;
	while (cmd->argv[i])
	{
		free (cmd->argv[i]);
		i++;
	}
	free (cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd *next;
	while (cmd)
	{
		next = cmd->next;
		free_single_cmd(cmd);
		cmd = next;
	}
}

void cleanup_parse(t_shell *shell, t_cmd *curr, t_cmd *head, char *msg)
{
	if (shell)
	{
		shell->commands = NULL;
		shell->last_exit_code = 2;
	}
	if (curr)
		free_single_cmd(curr);
	if (head)
		free_cmd_list(head);
	if (msg)
		print_error(msg);
}