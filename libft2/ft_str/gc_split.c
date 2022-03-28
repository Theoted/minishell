/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:30:06 by pat               #+#    #+#             */
/*   Updated: 2022/03/16 17:29:47 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

static int	wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*gc_strndup(t_track **track, char const *s, size_t size)
{
	size_t	i;
	char	*word;

	word = NULL;
	i = 0;
	word = gc_calloc((sizeof(char)), (size + 1), track);
	while (i < size && s[i])
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static size_t	count_word(char const *s, char c)
{
	size_t	count;

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

char	**gc_split(t_track **track, char const *s, char c)
{
	int			i;
	size_t		j;
	size_t		size;
	char		**newstring;

	newstring = NULL;
	i = 0;
	j = -1;
	if (!s)
		return (0);
	size = count_word(s, c);
	newstring = gc_calloc(sizeof(char *), (count_word(s, c) + 1), track);
	while (++j < size && *s)
	{
		while (*s == c)
			s++;
		i = wordlen(s, c);
		newstring[j] = gc_strndup(track, s, i);
		s += i;
	}
	newstring[j] = 0;
	return (newstring);
}
