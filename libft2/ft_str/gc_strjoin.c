/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:05:34 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 17:25:53 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

char	*gc_strjoin(t_track **track, char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	str = NULL;
	i = 0;
	j = 0;
	str = gc_calloc(sizeof(char), ((ft_strlen(s1) + ft_strlen(s2)) + 2), track);
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
