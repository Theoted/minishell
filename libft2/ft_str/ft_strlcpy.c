/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:57:11 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:58:30 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	l;

	l = ft_strlen(src);
	if (!size)
		return (l);
	while (*src && --size > 0)
		*dest++ = *src++;
	*dest = '\0';
	return (l);
}
