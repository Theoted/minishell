/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:38:11 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/04 17:52:58 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
