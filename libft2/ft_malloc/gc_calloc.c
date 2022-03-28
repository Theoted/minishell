/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:38:46 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 14:09:04 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

void	*gc_calloc(size_t count, size_t size, t_track **track)
{
	size_t	tot;
	void	*dst;

	tot = size * count;
	dst = malloc(tot);
	if (!(dst))
		return (NULL);
	ft_bzero(dst, tot);
	gc_add_mal(track, (void **)&dst);
	return (dst);
}
