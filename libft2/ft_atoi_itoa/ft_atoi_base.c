/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 01:57:22 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/16 17:40:10 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

int	strsame(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != s[j])
		{
			if (s[i] == s[j] && i != j)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	strlength(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	cbase(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	checkbase(char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ')
			return (0);
		i++;
	}
	if (strlength(base) < 2)
		return (0);
	if (strsame(base))
		return (0);
	return (1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	if (!checkbase(base))
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (cbase(str[i], base) != (-1))
	{
		result = result * strlength(base) + cbase(str[i], base);
		i++;
	}	
	return (result * sign);
}
