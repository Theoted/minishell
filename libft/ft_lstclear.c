/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:55:40 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/12 15:28:47 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst)
	{
		tmp = *lst;
		while (tmp)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, (del));
			*lst = tmp;
		}
		*lst = NULL;
	}
}
