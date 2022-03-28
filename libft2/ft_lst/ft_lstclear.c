/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:41:01 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:55:38 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = 0;
}
