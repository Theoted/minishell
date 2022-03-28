/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:41:07 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 00:48:04 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

static int	ft_whitespace(char c)
{
	return (((c >= 9) && (c <= 13)) || c == ' ');
}

static int	ft_overflow(long int nb)
{
	if (nb > 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long int	res;
	long int	neg;

	res = 0;
	neg = 1;
	if (!*str)
		return (0);
	while (ft_whitespace(*str) > 0)
		str++;
	if (*str == '-')
	{
		neg = -neg;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str) > 0)
	{
		res = res * 10 + (*str) - 48;
		str++;
		if (res > 2147483648)
			return (ft_overflow(res * neg));
	}
	return (res * neg);
}
