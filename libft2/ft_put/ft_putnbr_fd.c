/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 02:57:15 by pat               #+#    #+#             */
/*   Updated: 2022/03/11 01:57:09 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

int	ft_putnbr_fd(int n, int fd, int i)
{	
	if (fd == 0)
		return (0);
	else if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return (11);
	}
	else if (n < 0)
	{
		i = ft_putchar_fd('-', fd);
		i = ft_putnbr_fd(-n, fd, i);
	}
	else if (n >= 10)
	{	
		i = ft_putnbr_fd(n / 10, fd, i);
		i += ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		i += ft_putchar_fd(n + '0', fd);
	return (i);
}
