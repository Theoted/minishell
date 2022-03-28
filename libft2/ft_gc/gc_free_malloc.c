/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:04:38 by pat               #+#    #+#             */
/*   Updated: 2022/03/16 17:32:55 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"
#include "../include/libft.h"

void	gc_free_malloc(t_track **track, void **del)
{
	t_track	*tmp;

	tmp = *track;
	while (tmp)
	{
		if (tmp->address == *del)
		{
			if (tmp->prev && tmp->next)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			if (tmp->next && !tmp->prev)
			{
				tmp->next->prev = NULL;
				*track = (*track)->next;
			}
			if (!tmp->next && tmp->prev)
				tmp->prev->next = NULL;
			if (!tmp->next && !tmp->prev)
				*track = NULL;
			gc_lstdelone(tmp, free);
		}
		tmp = tmp->next;
	}
}
