/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:38:46 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 13:53:49 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	tot;
	void	*dst;

	tot = size * count;
	dst = malloc(tot);
	if (!(dst))
		return (NULL);
	ft_bzero(dst, tot);
	return (dst);
}
