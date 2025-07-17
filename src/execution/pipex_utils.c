/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex_utils.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/15 14:49:37 by mmatsui        #+#    #+#                */
/*   Updated: 2025/05/22 14:21:44 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_in_out_file(t_fds *fds, char **av)
{
	fds->infile = open (av[1], O_RDONLY);
	if (fds->infile < 0)
	{
		perror("infile");
		fds->infile = open("/dev/null", O_RDONLY);
		if (fds->infile < 0)
			clean_exit(fds, "fallback failed", 1);
	}
	fds->outfile = open (av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
		perror("outfile");
}

static char	*complete_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	full = ft_strjoin(temp, cmd);
	free (temp);
	return (full);
}

static char	**prep_all_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*find_path(t_cmd *cmd, char **envp)
{
	int		i;
	char	**all_path;
	char	*full;

	all_path = prep_all_path(envp);
	if (!all_path)
		return (NULL);
	if (!cmd->cmd_name)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		full = complete_path(all_path[i], cmd->cmd_name);
		if (access(full, X_OK) == 0)
			return (ft_free_split(all_path), full);
		free (full);
		i++;
	}
	ft_free_split(all_path);
	return (NULL);
}
