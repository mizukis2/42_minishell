/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   buildin_cd.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 18:13:12 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/19 18:13:14 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_home_path(char **envp)
{	
	int	i;
	
	i = 0;
	while (envp[i] && (ft_strncmp (envp[i], "HOME=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_strdup(envp[i] + 5));
}

int ft_cd(char **args, char **envp)
{
	char *path;
	char *home_path;

	if (args[2] != NULL)
		return (perror ("cd: too many arguments"), 1);
	else if (!args[1] || (ft_strcmp(args[1], '~') == 0))
	{
		home_path = get_home_path(envp);
		if (!home_path)
			return (perror("cd: HOME not set"), 1);
		path = home_path;
		free(home_path);
	}
	else if ((ft_strncmp(args[1], "~/", 2)) == 0)
	{
		home_path = get_home_path(envp);
		if (!home_path)
			return (perror("cd: HOME not set"), 1);
		path = ft_strjoin(home_path, args[1] + 1);
		free(home_path);
	}
	else if ((ft_strcmp(args[1], ".")) == 0)
		path = getcwd(NULL, 0);  //this getcwd used malloc
	else if ((ft_strcmp(args[1], "..")) == 0)
		path = ft_strjoin(getcwd(NULL, 0), "/..");
	else 
		path = args[1];

	if (chdir(path)!= 0)
		return (0);


	//free path
	//data management (not yet)
}

