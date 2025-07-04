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

void	set_new_env(const char *new_env_value, char ***envp)
{
	char **new_envp;
	int	i;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc (sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = -1;
	while ((*envp)[++i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (!new_envp[i])
			return (free_array(new_envp));
	}
	new_envp[i] = ft_strdup(new_env_value);
	if (!new_envp[i])
    	return(free_array(new_envp));
	new_envp[i + 1] = NULL;
	free_array(*envp);
	*envp = new_envp;
}

void	update_env_var(const char *key, const char *path, char ***envp)
{
	int	index;
	char *new_env_value;
	char **new_envp;
	new_env_value = ft_strjoin(key, path);
	if (!new_env_value)
		return ;
	index = find_path_index(key, (*envp));
	if (index < 0)
	{
		set_new_env(new_env_value, envp);
		free (new_env_value);
		return ;
	}
	new_envp = env_dup((*envp));
	if (!new_envp)
		return (free(new_env_value));
	free (new_envp[index]);
	new_envp[index] = ft_strdup(new_env_value);
	free(new_env_value);
	if (!new_envp[index])
		return (free_array(new_envp));
	free_array(*envp);
	(*envp) = new_envp;
}


/*--------------------------------------------------------------------- */

static int	check_cd_arg(char **args)
{
	if (count_args(args) > 3)
		return (print_error("cd: too many arguments\n"), 1);
	return (0);
}

char *find_home_path(t_env *envp)
{
	char *env_line;
	t_env *curr;

	curr = envp;
	while (curr)
	{
		if(ft_strcmp(envp->key, "HOME"))
			return (envp->value);
		curr = curr->next;
	}
	return (NULL);
}


char	*home_related_path(char *arg, t_env *envp)
{
	char	*home_path;
	char	*result_path;

	home_path = find_home_path(envp);
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

char *resolve_path(char *arg, t_env *envp)
{
	char *result_path;
	if (!arg || arg == '~' || (ft_strncmp(arg, "~/", 2)) == 0)
		return (home_related_path);
	else if (arg == '-')
	{
		//go back the previous 
	}

}


int	ft_cd(char **args, t_env *envp)
{
	char	*path;
	char	*oldpwd;
	char	*cwd;

	if (check_cd_arg(args))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd: no current working dir"), 1);
	path = resolve_path(args[1], envp);
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
#include <stdio.h>
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
	char *args6[] = {"cd", "-", NULL};
	char *args7[] = {"cd", ".", NULL};
	char *args8[] = {"cd", "..", NULL};

	run_test(args1, envp_mock);
	run_test(args2, envp_mock);
	run_test(args3, envp_mock);
	run_test(args4, envp_mock);
	run_test(args5, envp_mock);
	run_test(args6, envp_mock);
	run_test(args7, envp_mock);
	run_test(args8, envp_mock);
}

