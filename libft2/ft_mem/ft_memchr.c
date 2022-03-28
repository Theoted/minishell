/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:45:07 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:56:07 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	if (!(unsigned char)c && n)
		return ((void *)&s[ft_strlen((char *)str)]);
	while (n && n--)
		if ((unsigned char)c == *str++)
			return (--str);
	return (NULL);
}
