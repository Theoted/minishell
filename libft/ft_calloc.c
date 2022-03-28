/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:32:43 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/04 17:55:19 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	int		i;

	mem = malloc(size * count);
	i = 0;
	if (!mem)
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}
