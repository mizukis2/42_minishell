/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 04:09:31 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 08:18:01 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	print_tokens(t_token *tokens)//for token debug
{
	while (tokens)
	{
		printf("TOKEN TYPE: %d, VALUE: [%s]\n",
			tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

static const char *rtype_name(t_rtype t)
{
    if (t == R_IN)  return "R_IN";
    if (t == R_OUT) return "R_OUT";
    if (t == R_APPEND) return "R_APP";
    return "R_HERE";
}

static void print_cmd(t_cmd *cmd)
{
    int idx_cmd = 0;
    while (cmd) {
        printf("\nCommand #%d:\n", ++idx_cmd);

        // argv
        if (cmd->argv) {
            for (int i = 0; cmd->argv[i]; i++)
                printf("  argv[%d]: %s\n", i, cmd->argv[i]);
        } else {
            printf("  (no argv)\n");
        }

        // redirs
        printf("  Redirections:\n");
        if (cmd->redirs) {
            int i = 0;
            for (t_redir *r = cmd->redirs; r; r = r->next, i++)
                printf("    redir[%d]: type=%s, target=%s, here=%s\n",
                       i, rtype_name(r->type), r->target, r->is_heredoc ? "yes" : "no");
        } else {
            printf("    (none)\n");
        }

        cmd = cmd->next;
    }
}
 */
static int	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->last_exit_code = 0;
	shell->env_list = copy_initial_env(envp);
	if (!shell->env_list)
	{
		print_error("ERROR - Unable to make list of Environment Variables");
		shell->last_exit_code = 1;
		return (0);
	}
	return (1);
}

void	clean_shell(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->commands)
		free_cmd_list(shell->commands);
	if (shell->tokens)
		free_tokens(shell->tokens);
}

static void	free_env(t_env *head)
{
	return (free_node_list(head));
}

int	start_shell(char **envp)
{
	t_shell	shell;
	int		code;

	if (!init_shell(&shell, envp))
		return (1);
	while (1)
	{
		shell.line = readline("\033[38;2;0;206;209mMZ$hell\033[0m$ ");
		if (!shell.line) // check for EOF Ctrl+D (temporary)
		{
			write (1, "exit\n", 5);
			break ;
		}
		if (!is_valid_input(&shell))
			continue ;
		add_history(shell.line);
		if (!tokenize_input(&shell))
			continue ;
		if (!parse_tokens(&shell))
			continue ;
		run_execution (&shell);
		cleanup(&shell);
	}
	code = shell.last_exit_code;
	free_env(shell.env_list);
	return (code);
}
