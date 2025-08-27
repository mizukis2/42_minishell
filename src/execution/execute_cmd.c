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

static int	map_exec_errno(int e)
{
	if (e == ENOENT)
		return (127);
	if (e == EACCES || e == EINVAL)
		return (126);
	return (126);
}

static void	exec_fail(const char *path, t_shell *shell, int err)
{
	print_error_errno(path, err);
	clean_exit(shell, NULL, NULL, map_exec_errno(err));
}

static void	exec_explicit_path(char**argv, t_shell *shell)
{
	struct stat	st;
	const char	*path;
	char		**array_envp;
	int			e;

	path = argv[0];
	if (stat(path, &st) != 0)
		exec_fail(path, shell, errno);
	if (S_ISDIR(st.st_mode))
		exec_fail(path, shell, EISDIR);
	if (access(path, X_OK) != 0)
		exec_fail(path, shell, errno);
	array_envp = list_to_array(shell->env_list);
	execve (path, argv, array_envp);
	e = errno;
	free (array_envp);
	exec_fail(path, shell, e);
}

static void	exec_fail_free(char *path, char **array_envp,
	t_shell *shell, int err)
{
	free (path);
	free_array(array_envp);
	exec_fail(path, shell, err);
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
	exec_fail_free(path, array_envp, shell, e);
}
