/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:08:00 by tdeville          #+#    #+#             */
/*   Updated: 2021/12/29 10:08:22 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *s, size_t size)
{
	size_t		i;
	char		*word;

	i = 0;
	word = malloc((sizeof(char) * size) + 1);
	if (!word)
		return (0);
	while (i < size && s[i])
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
