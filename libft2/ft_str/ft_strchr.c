/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:25:58 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:58:17 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		if ((char)c == '\0')
			return ((char *)&s[ft_strlen(s)]);
		while (*s)
		{
			if (*s == (char)c)
				return ((char *)s);
			s++;
		}
	}
	return (0);
}
