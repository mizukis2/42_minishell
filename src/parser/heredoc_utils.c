/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   heredoc_utils.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/27 15:00:29 by mmatsui        #+#    #+#                */
/*   Updated: 2025/08/27 15:00:31 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_delim_quotes(const char *str, bool *quoted)
{
	char	*unquoted_delim;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	unquoted_delim = malloc (len + 1);
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

static int	create_temp_heredoc(char **out_path)
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
			return (free (i_ascii), -1);
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

static void	collect_heredoc(int fd, char *delim, bool is_quoted, t_shell *shell)
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
		if (is_quoted)
			value = ft_strdup(line);
		else
			value = expand_heredoc_variables(line, shell);
		write(fd, value, ft_strlen(value));
		write(fd, "\n", 1);
		free(value);
		free(line);
	}
}

char	*create_heredoc_file(const char *delim, t_shell *shell)
{
	t_heredoc	heredoc;
	bool		quoted;

	heredoc.clean_delim = strip_delim_quotes(delim, &quoted);
	heredoc.is_quoted = quoted;
	if (!heredoc.clean_delim)
		return (NULL);
	heredoc.fd = create_temp_heredoc(&heredoc.temp_path);
	if (heredoc.fd < 0)
		return (free(heredoc.clean_delim), NULL);
	collect_heredoc(heredoc.fd, heredoc.clean_delim,
		heredoc.is_quoted, shell);
	free(heredoc.clean_delim);
	close(heredoc.fd);
	return (heredoc.temp_path);
}
//signal memo
//shell->last_exit_code = 130
//unlink (heredoc.temp_path)
//return NULL
