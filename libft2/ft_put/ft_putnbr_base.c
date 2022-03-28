/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 00:47:22 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:57:07 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

unsigned int	ft_strcmp(char *str)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}	
	return (0);
}

unsigned int	indx(char *str)
{
	unsigned int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned int	check(char *base)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (indx(base) < 2)
		return (0);
	if (ft_strcmp(base))
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_base(unsigned int n, char *base, int i)
{
	unsigned int	idx;

	idx = indx(base);
	if (check(base))
	{
		if (n >= idx)
			i = ft_putnbr_base(n / idx, base, i);
		i += ft_putchar_fd(base[n % idx], 1);
	}	
	return (i);
}
