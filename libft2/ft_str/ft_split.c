/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:30:06 by pat               #+#    #+#             */
/*   Updated: 2022/03/16 17:28:46 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

static char	**freeall(char **str, int n)
{
	n++;
	while (n--)
		free(str[n]);
	free(str);
	return (0);
}

static int	wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_strndup(char const *s, size_t size)
{
	size_t	i;
	char	*word;

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

static int	count_word(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	char	**newstring;

	i = 0;
	j = -1;
	if (!s)
		return (0);
	size = count_word(s, c);
	newstring = ft_calloc(sizeof(char *), (count_word(s, c) + 1));
	if (!newstring)
		return (0);
	while (++j < size && *s)
	{
		while (*s == c)
			s++;
		i = wordlen(s, c);
		newstring[j] = ft_strndup(s, i);
		if (!newstring[j])
			return (freeall(newstring, j));
		s += i;
	}
	newstring[j] = 0;
	return (newstring);
}
