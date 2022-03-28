/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:33:54 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/12 18:44:58 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*res;

	res = NULL;
	if (lst)
	{
		while (lst)
		{
			new = ft_lstnew(f(lst->content));
			if (!new)
			{
				ft_lstclear(&res, del);
				return (NULL);
			}
			ft_lstadd_back(&res, new);
			lst = lst->next;
		}
	}
	return (res);
}
