/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 02:42:13 by zekhatib          #+#    #+#             */
/*   Updated: 2025/03/18 21:04:24 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!newline_exists(buffer) && bytes_read != 0)
	{
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (NULL);
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if ((!buffer && bytes_read == 0) || bytes_read == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = gnl_strjoin(buffer, temp);
	}
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1 + newline_exists(buffer)));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*extract_leftover(char *line, char *buffer)
{
	char	*leftover;
	int		i;
	int		j;

	i = ft_strlen(line);
	j = 0;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	leftover = malloc(sizeof(char) * ft_strlen(buffer) - i + 1);
	if (!leftover)
		return (NULL);
	while (buffer[i])
	{
		leftover[j] = buffer[i];
		i++;
		j++;
	}
	leftover[j] = '\0';
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	temp = read_line(fd, buffer[fd]);
	if (!temp)
	{
		if (buffer[fd])
			free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = temp;
	line = extract_line(buffer[fd]);
	if (!line)
	{
		if (buffer[fd])
			free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = extract_leftover(line, buffer[fd]);
	return (line);
}
