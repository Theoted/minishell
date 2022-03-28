/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_usigned_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:11:09 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:57:15 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

int	ft_putnbr_usigned_fd(unsigned int n, int fd, int i)
{	
	if (fd == 0)
		return (0);
	else if (n >= 10)
	{	
		i = ft_putnbr_fd(n / 10, fd, i);
		i += ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		i += ft_putchar_fd(n + '0', fd);
	return (i);
}
