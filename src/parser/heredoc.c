/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:45:45 by zekhatib          #+#    #+#             */
/*   Updated: 2025/08/06 09:12:27 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			value = expand_variables(line, shell);
		write(fd, value, ft_strlen(value));
		write(fd, "\n", 1);
		free(value);
		free(line);
	}
}

static char	*create_heredoc_file(const char *delim, t_shell *shell)
{
	t_heredoc	heredoc;

	if ((delim[0] == '\'' && delim[ft_strlen(delim) - 1] == '\'')
		|| (delim[0] == '"' && delim[ft_strlen(delim) - 1] == '"'))
	{
		heredoc.clean_delim = ft_strndup(delim + 1, ft_strlen(delim) - 2);
		heredoc.is_quoted = true;
	}
	else
	{
		heredoc.clean_delim = ft_strdup(delim);
		heredoc.is_quoted = false;
	}
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
//shell->last_exit_code = 130
//unlink (heredoc.temp_path)
//return NULL

static char	*expect_delim_no_expand(t_token **tokens, t_shell *shell,
										t_cmd *cmd)
{
	char	*str;

	if (!tokens || !*tokens || (*tokens)->type != TOKEN_WORD)
	{
		shell->last_exit_code = 2;
		cmd->invalid = true;
		return (NULL);
	}
	str = ft_strdup((*tokens)->value);
	if (!str)
	{
		shell->last_exit_code = 1;
		cmd->invalid = true;
		return (NULL);
	}
	*tokens = (*tokens)->next;
	return (str);
}

void	handle_heredoc_redir(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_token	*tok;
	char	*delim;
	char	*path;

	tok = *tokens;
	delim = expect_delim_no_expand(tokens, shell, cmd);
	if (!delim)
	{
		cmd->invalid = true;
		return ;
	}
	path = create_heredoc_file(delim, shell);
	free(delim);
	if (!path)
	{
		cmd->invalid = true;
		return ;
	}
	if (!add_redir(&cmd->redirs, R_HEREDOC, path, true))
	{
		free(path);
		shell->last_exit_code = 1;
		cmd->invalid = true;
		return ;
	}
	free (path);
}
