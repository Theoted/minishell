/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:58:59 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:56:16 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

static void	*ft_memrcpy(void *dest, const void *src, size_t len)
{
	while (len--)
		((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest <= src)
		return (ft_memcpy(dest, src, len));
	else
		return (ft_memrcpy(dest, src, len));
}
