/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:08:30 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:57:18 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

int	ft_putptr_rec(unsigned long nbr)
{
	const char	*base = "0123456789abcdef";

	if (nbr < 16)
		return (write(1, base + nbr, 1));
	return (ft_putptr_rec(nbr / 16) + write(1, base + (nbr % 16), 1));
}

int	ft_putptr(unsigned long long nbr, int i)
{
	write(1, "0x", 2);
	i += 2;
	i += ft_putptr_rec(nbr);
	return (i);
}
