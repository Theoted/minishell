/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:31:52 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 17:51:06 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

char	*gc_itoa(t_track **track, int n)
{	
	long	nb;
	char	*str;
	int		i;

	str = NULL;
	i = 1;
	nb = n;
	if (n < 0)
		nb = -nb + 0 * i++;
	while (nb >= 10)
		nb /= 10 + 0 * i++;
	nb = n;
	if (nb < 0)
		nb = -nb;
	str = gc_calloc(sizeof(char), (i + 1), track);
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	while (nb >= 10)
	{
		str[--i] = nb % 10 + 48;
		nb /= 10;
	}
	str[--i] = nb % 10 + 48;
	return (str);
}
