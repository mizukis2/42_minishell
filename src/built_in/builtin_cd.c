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

static char	*resolve_home_path(char *arg, char **envp)
{
	char	*home_path;
	char	*result_path;

	home_path = get_home_path(envp);
	if (!home_path)
		return (NULL);
	if (!arg || (ft_strcmp(arg, "~") == 0))
		return (home_path);
	if ((ft_strncmp(arg, "~/", 2)) == 0)
	{
		result_path = ft_strjoin(home_path, arg + 1);
		if (!result_path)
			return (free(home_path), NULL);
		free(home_path);
		return (result_path);
	}
	free(home_path);
	return (NULL);
}

static int	check_cd_arg(char **args)
{
	if (count_args(args) > 3)
		return (print_error("cd: too many arguments\n"), 1);
	return (0);
}

int	ft_cd(char **args, char ***envp)
{
	char	*path;
	char	*oldpwd;
	char	*cwd;

	if (check_cd_arg(args))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd: no current working dir"), 1);
	path = resolve_home_path(args[1], (*envp));
	if (!path && args[1])
		path = ft_strdup(args[1]);	
	if (!path || chdir(path) != 0)
		return (perror ("cd"),free(oldpwd), free(path), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd: cannot get cwd"), free(oldpwd), free(path), 1);
	update_env_var("OLDPWD=", oldpwd, envp);
	update_env_var("PWD=", cwd, envp);
	return (free(oldpwd), free(cwd),free (path), 0);
}
/* #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void run_test(char **args, char **envp)
{
	char **copy_envp = env_dup(envp);
	if (!copy_envp)
		return (perror("env_dup failed"), (void)0);
	
	int result = ft_cd(args, &copy_envp);
	printf("\nReturn: %d\nUpdated environment:\n", result);
	for (int i = 0; copy_envp[i]; i++)
		printf("%s\n", copy_envp[i]);
	free_array(copy_envp);
	printf("--------------\n");
}

int main(void)
{
	char *envp_mock[] = {
		"HOME=/home/mmatsui",
		"PWD=/home/mmatsui/A_subject/minishell",
		"OLDPWD=/tmp",
		NULL
	};

	char *args1[] = {"cd", NULL};
	char *args2[] = {"cd", "~", NULL};
	char *args3[] = {"cd", "~/testfolder", NULL};
	char *args4[] = {"cd", "/tmp", NULL};
	char *args5[] = {"cd", "one", "two", NULL};

	run_test(args1, envp_mock);
	run_test(args2, envp_mock);
	run_test(args3, envp_mock);
	run_test(args4, envp_mock);
	run_test(args5, envp_mock);
}

 */