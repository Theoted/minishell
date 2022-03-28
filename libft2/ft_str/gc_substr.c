/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:46:39 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 17:46:34 by pat              ###   ########lyon.fr   */
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
		length = size - 1;
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
