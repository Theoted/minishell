/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:01:31 by tdeville          #+#    #+#             */
/*   Updated: 2021/12/06 12:23:19 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			length;
	unsigned int	j;
	char			*str;

	i = 0;
	j = start;
	length = len;
	if (!s)
		return (0);
	if (ft_strlen(s) < len)
		length = ft_strlen(s) - 1;
	str = malloc((sizeof(char) * length) + 1);
	if (!str)
		return (0);
	while (i < len && s[j] && (j < ft_strlen(s)))
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
