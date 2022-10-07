/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_malloc_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:04:38 by pat               #+#    #+#             */
/*   Updated: 2022/10/07 02:12:29 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"
#include "../include/libft.h"

void	gc_free_malloc_split_while(t_track **track, void ***del, t_track *tmp)
{
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
			gc_lstdelone(&tmp, free);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	gc_free_malloc_split(t_track **track, void ***del)
{
	t_track	*tmp;

	tmp = *track;
	gc_free_malloc_split_while(track, del, tmp);
}
