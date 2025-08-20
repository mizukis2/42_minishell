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

static int map_exec_errno(int e)
{
	if (e == ENOENT)
		return (127);
	if (e == EACCES || e == EINVAL)
		return (126);
	return (126);
}

static void	exec_explicit_path(char**argv, t_shell *shell)
{
	struct stat	st;
	const char *path;
	char **array_envp;
	int		e;

	path = argv[0];
	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_error_errno(path, EISDIR);
			clean_exit(shell, NULL, NULL, 126);
		}
		if (access(path, X_OK) != 0)
		{
			e = errno;
			print_error_errno(path, e);
			clean_exit(shell, NULL, NULL, map_exec_errno(e));	
		}
	}
	else
	{
		e = errno;
		print_error_errno(path, e);
		clean_exit(shell, NULL, NULL, map_exec_errno(e));
	}
	array_envp = list_to_array(shell->env_list);
	execve (path, argv, array_envp);
	e = errno;
	print_error_errno(path, e);
	free (array_envp);
	clean_exit(shell, NULL, NULL, map_exec_errno(e));
}

/* child process, exit with exit_code if fails */
void	execute_command(char **argv, t_shell *shell)
{
	char		*path;
	char		**array_envp;
	int			exit_code;
	int			e;

	if (!argv || !argv[0] || argv[0][0] == '\0')
		clean_exit(shell, "Command not found\n", NULL, 127);
	if (is_builtin(argv))
	{
		exit_code = execute_builtin(argv, shell->env_list);
		cleanup_child(shell);
		exit (exit_code);
	}
	if (ft_strchr(argv[0], '/'))
		exec_explicit_path(argv, shell);
	path = find_path(argv[0], shell->env_list);
	if (!path)
		clean_exit(shell, "Command not found: ", argv[0], 127);
	cleanup_child(shell);
	array_envp = list_to_array(shell->env_list);
	execve (path, argv, array_envp);
	e = errno;
	print_error_errno(path, e);
	free (array_envp);
	free (path);
	clean_exit(shell, NULL, NULL, map_exec_errno(e));
}
