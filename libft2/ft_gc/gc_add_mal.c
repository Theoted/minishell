/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add_mal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:52:46 by pat               #+#    #+#             */
/*   Updated: 2022/03/16 17:33:28 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"
#include "../include/libft.h"

void	gc_add_mal(t_track **track, void **address)
{
	if (!(*track))
		*track = gc_lstnew(address);
	else
		gc_lstadd_front(track, gc_lstnew(address));
}
