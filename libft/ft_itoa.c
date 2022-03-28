/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:07:34 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/07 17:19:04 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	intlen(long n)
{
	int	len;

	len = 0;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

static long	isneg(long num, int *neg)
{
	if (num < 0)
	{
		*neg = 1;
		num = -num;
	}
	return (num);
}	

char	*ft_itoa(int n)
{
	char	*dst;
	int		neg;
	int		i;
	long	num;

	neg = 0;
	num = n;
	num = isneg(num, &neg);
	i = neg + intlen(num);
	dst = malloc((sizeof(char) * intlen(num)) + 1 + neg);
	if (!dst)
		return (0);
	dst[i--] = '\0';
	while (num > 9)
	{
		dst[i] = num % 10 + 48;
		num /= 10;
		i--;
	}
	dst[i] = num + 48;
	if (neg)
		dst[--i] = '-';
	return (dst);
}
