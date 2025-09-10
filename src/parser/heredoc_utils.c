/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:00:29 by mmatsui           #+#    #+#             */
/*   Updated: 2025/09/09 06:15:55 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_delim_quotes(const char *str, bool *quoted)
{
	char	*unquoted_delim;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	unquoted_delim = malloc(len + 1);
	if (!unquoted_delim)
		return (NULL);
	*quoted = false;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			*quoted = true;
		else
			unquoted_delim[j++] = str[i];
		i++;
	}
	unquoted_delim[j] = '\0';
	return (unquoted_delim);
}

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
			return (free(i_ascii), -1);
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

static void	printvalue(int fd, char *value)
{
	write(fd, value, ft_strlen(value));
	write(fd, "\n", 1);
}

void	collect_hd(int fd, char *delim, bool quoted, t_shell *shell)
{
	char	*line;
	char	*value;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (quoted)
			value = ft_strdup(line);
		else
			value = expand_heredoc_variables(line, shell);
		if (!value)
		{
			free(line);
			close(fd);
			_exit(1);
		}
		printvalue(fd, value);
		free(value);
		free(line);
	}
}
