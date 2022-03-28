/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:41:44 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/05 12:11:54 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*source;

	i = 0;
	dest = dst;
	source = src;
	if ((!dest && !src) && n > 0)
		return (0);
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
