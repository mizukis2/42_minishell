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
