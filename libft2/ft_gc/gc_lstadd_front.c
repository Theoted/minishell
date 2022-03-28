/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:30:46 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 17:31:31 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"
#include "../include/libft.h"

void	gc_lstadd_front(t_track **track, t_track *new)
{
	if (!track || !new)
		return ;
	new->next = *track;
	(*track)->prev = new;
	*track = new;
}
