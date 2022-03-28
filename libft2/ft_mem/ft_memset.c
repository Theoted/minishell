/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:21:16 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:56:19 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

void	*ft_memset(void *str, int value, size_t count)
{
	int	i;

	i = count;
	while (count-- > 0)
		*(unsigned char *)str++ = (unsigned char)value;
	return (str - i);
}
