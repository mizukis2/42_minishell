/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execute_cmd.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/28 12:08:16 by mmatsui        #+#    #+#                */
/*   Updated: 2025/07/28 12:08:18 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*complete_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	full = ft_strjoin(temp, cmd);
	free (temp);
	return (full);
}

static char	**prep_all_path(t_env *envp)
{
	t_env	*curr;

	curr = envp;
	while (curr && ft_strcmp(curr->key, "PATH") != 0)
		curr = curr->next;
	if (!curr)
		return (NULL);
	return (ft_split(curr->value, ':'));
}

static char	*find_path(char *cmd, t_env *envp)
{
	int		i;
	char	**all_path;
	char	*full;

	all_path = prep_all_path(envp);
	if (!all_path)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		full = complete_path(all_path[i], cmd);
		if (access(full, X_OK) == 0)
			return (free_split(all_path), full);
		free (full);
		i++;
	}
	free_split(all_path);
	return (NULL);
}

/* child process, exit with exit_code if fails */
void	execute_command(char **argv, t_exec exec, t_shell *shell)
{
	char	*path;
	char	**array_envp;

	if (!argv || !argv[0])
		clean_exit(exec, "Command not found", NULL, 127);
	if (is_builtin(argv))
	{
		cleanup_child(exec);
		if (run_in_parent(argv))
			exit(0);
		exit (execute_builtin(argv, shell->envp));
	}
	path = find_path(argv[0], shell->envp);
	if (!path)
		clean_exit(exec, "Command not found: ", argv[0], 127);
	cleanup_child(exec);
	array_envp = list_to_array(shell->envp);
	execve (path, argv, array_envp);
	perror ("execve failed");
	free (path);
	exit (126);
}