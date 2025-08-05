/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:45:45 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/04 02:20:19 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_temp_heredoc(char **out_path)
{
	size_t	i;
	char	*path;
	int		fd;
	char	*i_ascii;

	i = 0;
	while (i < 10000)
	{
		i_ascii = ft_itoa(i);
		if (!i_ascii)
			return (-1);
		path = ft_strjoin("/tmp/.heredoc_", i_ascii);
		if (!path)
			return (-1);
		free(i_ascii);
		fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
		{
			*out_path = path;
			return (fd);
		}
		free(path);
		i++;
	}
	return (-1);
}
// in execution
// if (cmd->heredoc && cmd->infile)
// {
// 	unlink(cmd->infile);
// 	free(cmd->infile);
// }

void	collect_heredoc(int fd, char *delim, t_token *next, t_shell *shell)
{
	char	*value;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (next->quote_type != QUOTE_NONE)
			value = ft_strdup(line);
		else
			value = expand_variables(line, shell);
		write(fd, value, ft_strlen(value));
		write(fd, "\n", 1);
		free(value);
		free(line);
	}
}
