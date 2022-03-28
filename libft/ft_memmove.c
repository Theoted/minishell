/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:42:25 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/05 12:19:15 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dest;
	const char	*source;

	i = -1;
	dest = dst;
	source = src;
	if (!dest && !src && len > 0)
		return (0);
	if (src < dst)
	{
		while (len)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			dest[i] = source[i];
	}
	return (dest);
}
