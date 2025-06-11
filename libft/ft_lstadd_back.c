/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:24:29 by zekhatib          #+#    #+#             */
/*   Updated: 2024/11/01 17:41:22 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastnode;

	if (!lst || !new)
	{
		return ;
	}
	lastnode = ft_lstlast(*lst);
	if (!lastnode)
	{
		*lst = new;
	}
	else
	{
		lastnode->next = new;
	}
}
