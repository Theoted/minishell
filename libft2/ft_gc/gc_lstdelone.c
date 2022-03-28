/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:55:57 by pat               #+#    #+#             */
/*   Updated: 2022/03/18 16:49:13 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"
#include "../include/libft.h"

void	gc_lstdelone(t_track *lst, void (*del)(void*))
{
	if (lst)
	{
		if (lst->address)
		{
			del(lst->address);
			lst->address = NULL;
			lst->next = NULL;
			free(lst);
		}
	}
}
