/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zekhatib <zekhatib@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:04:43 by zekhatib          #+#    #+#             */
/*   Updated: 2024/10/30 21:12:23 by zekhatib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*templst;

	if (!lst)
		return (NULL);
	templst = lst;
	while (templst-> next != NULL)
	{
		templst = templst->next;
	}
	return (templst);
}
