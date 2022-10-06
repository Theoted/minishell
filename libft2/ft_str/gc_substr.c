/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:46:39 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/05 21:02:25 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

char	*gc_substr(t_track **track, const char *s,
			unsigned int start, size_t len)
{
	size_t			i;
	size_t			length;
	size_t			size;
	unsigned int	j;
	char			*str;

	i = 0;
	j = start;
	length = len;
	size = ft_strlen(s);
	if (!s)
		return (0);
	if (size < len)
		length = size;
	str = gc_calloc(sizeof(char), length + 1, track);
	if (!str)
		return (0);
	while (i < len && s[j] && (j < size))
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
