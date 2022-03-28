/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:35:08 by pat               #+#    #+#             */
/*   Updated: 2022/03/11 01:58:47 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

int	is_charset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_malloc_size(int i, int j)
{
	if (i <= j)
		return (j - i + 2);
	return (1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	while (s1[i] && is_charset(s1[i], set))
		i++;
	while (j && is_charset(s1[j], set))
		j--;
	ret = malloc(sizeof(char) * get_malloc_size(i, j));
	if (!ret)
		return (NULL);
	while (i < j + 1)
	{
		ret[k] = s1[i];
		k++;
		i++;
	}
	ret[k] = '\0';
	return (ret);
}
