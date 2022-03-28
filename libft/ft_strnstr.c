/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:22:07 by tdeville          #+#    #+#             */
/*   Updated: 2021/11/13 15:59:13 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int	check_strstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;

	i = 0;
	j = 0;
	n_len = ft_strlen(needle);
	while ((haystack[i] == needle[j]) && needle[j] && (i < len))
	{
		i++;
		j++;
	}
	if (j == n_len)
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!ft_strncmp(needle, "", ft_strlen(needle)))
		return ((char *)haystack);
	while (haystack[j] && (i < len))
	{
		if (check_strstr(&haystack[j], needle, len - j))
			return ((char *)&haystack[j]);
		i++;
		j++;
	}
	return (0);
}
