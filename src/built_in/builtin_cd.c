/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmatsui <mmatsui@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/19 18:13:12 by mmatsui       #+#    #+#                 */
/*   Updated: 2025/06/30 15:31:47 by matsuimiki    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "builtin.h"

static bool	is_cd_arg(char **args)
{
	if (count_args(args) > 1)
		return (false);
	return (true);
}

static char	*home_related_path(char *arg, t_env *envp)
{
	char	*home_path;
	char	*result_path;

	home_path = get_env_value(envp, "HOME");
	if (!home_path)
		return (print_error("cd: HOME not set\n"), NULL);
	if (!arg || ft_strcmp(arg, "~") == 0)
		return (home_path);
	if (ft_strncmp(arg, "~/", 2) == 0)
	{
		result_path = ft_strjoin(home_path, arg + 1);
		free(home_path);
		return (result_path);
	}
	free(home_path);
	return (NULL);
}

static char	*resolve_path(char *arg, t_env *envp)
{
	char	*result_path;

	if (!arg || ft_strcmp(arg, "~") == 0 || ft_strncmp(arg, "~/", 2) == 0)
	{
		result_path = home_related_path(arg, envp);
		if (!result_path)
			return (NULL);
		return (result_path);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		result_path = get_env_value(envp, "OLDPWD");
		if (!result_path)
			return (print_error("cd: OLDPWD not set\n"), NULL);
		ft_putstr(result_path);
		write (STDOUT_FILENO, "\n", 1);
		return (result_path);
	}
	else
		return (ft_strdup(arg));
}

static void	set_error_return(char *cd_arg, char *oldpwd, char *path)
{
	print_error("cd: ");
	if (cd_arg)
		print_error(cd_arg);
	print_error(": ");
	perror("");
	free (oldpwd);
	free(path);
}

int	ft_cd(char **args, t_env *envp)
{
	char	*path;
	char	*oldpwd;
	char	*cwd;

	if (is_cd_arg(args) == false)
		return (print_error("cd: too many arguments\n"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (print_error("cd"), 1);
	path = resolve_path(args[0], envp);
	if (!path)
		return (free(oldpwd), 1);
	if (path && path[0] == '\0')
		return (free(oldpwd), free(path), 0);
	if (chdir(path) != 0)
		return (set_error_return(args[0], oldpwd, path), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (print_error("cd"), free(oldpwd), free(path), 1);
	update_env("OLDPWD", oldpwd, envp);
	update_env("PWD", cwd, envp);
	return (free(oldpwd), free(cwd), free (path), 0);
}
