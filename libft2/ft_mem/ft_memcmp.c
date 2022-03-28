/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:52:11 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/11 01:56:10 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	if (!n)
		return (0);
	while ((*((unsigned char *)p1++) == (*(unsigned char *)p2++)) && --n > 0)
		;
	return (*((unsigned char *)--p1) - (*(unsigned char *)--p2));
}
