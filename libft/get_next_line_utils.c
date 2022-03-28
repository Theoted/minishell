/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:09:11 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/22 10:55:51 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str, int n)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (n == 0)
	{
		while (str[i])
			i++;
		return (i);
	}
	else
	{
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] && str[i] == '\n')
			i++;
		return (i);
	}
	return (0);
}
