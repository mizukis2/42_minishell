/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   cleaning.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mmatsui <mmatsui@student.codam.nl>            +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/12 13:14:32 by mmatsui        #+#    #+#                */
/*   Updated: 2025/06/12 13:14:34 by mmatsui        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this is just an idea, we will update later


void	ft_free_split(char **split_list)
{
	int	i;

	if (!split_list)
		return ;
	i = 0;
	while (split_list[i])
	{
		free (split_list[i]);
		i++;
	}
	free(split_list);
}