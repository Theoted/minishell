/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:58:46 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 17:20:08 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest);
}

char	*gc_strdup(t_track **track, const char *src)
{
	char	*dest;

	dest = gc_calloc(sizeof(char), ft_strlen(src) + 1, track);
	if (!dest)
		return (0);
	ft_strcpy(dest, src);
	return (dest);
}
