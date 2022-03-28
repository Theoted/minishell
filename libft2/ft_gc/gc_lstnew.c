/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:08:44 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 17:33:45 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"
#include "../include/libft.h"

t_track	*gc_lstnew(void **address)
{
	t_track	*lstnew;

	lstnew = malloc(sizeof(t_track));
	if (!lstnew)
		return (0);
	lstnew->address = *address;
	lstnew->next = NULL;
	lstnew->prev = NULL;
	return (lstnew);
}
