/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:14:32 by mmatsui           #+#    #+#             */
/*   Updated: 2025/07/28 00:23:27 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *msg)
{
	write(2, PURPLE, sizeof(PURPLE) - 1);
	write(2, "MZ$hell: ", 9);
	write(2, RED, sizeof(RED) - 1);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	write(2, RESET, sizeof(RESET) - 1);
}

void	print_error_builtin(const char *msg)
{
	write (STDERR_FILENO, msg, ft_strlen(msg));
}

void	print_error_errno(const char *path, int err)
{
	const char	*msg;
	size_t		msg_len;
	size_t		plen;

	msg = strerror(err);
	msg_len = ft_strlen(msg);
	write(2, "MZ$hell: ", 9);
	if (path && *path)
	{
		plen = ft_strlen(path);
		write(2, path, plen);
		write(2, ": ", 2);
	}
	write(2, msg, msg_len);
	write(2, "\n", 1);
}
