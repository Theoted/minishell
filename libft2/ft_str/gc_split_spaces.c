/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:51:51 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/18 16:46:10 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"
#include "../../includes/minishell.h"

static int	wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && !state_checker((char *)s, 0, i))
			return (i);
		i++;
	}
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
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (state_checker((char *)s, 0, i))
			i++;
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	find_next_idx(char *s, int idx)
{
	int	j;

	j = 0;
	while (s[idx])
	{
		if (s[idx] == ' ' && !state_checker(s, 0, idx))
			return (idx);
		idx++;
	}
	return (idx);
}

char	**gc_split_spaces(t_track **track, char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	char	**newstring;
	
	i = 0;
	j = -1;
	size = (count_word(s, c));
	newstring = gc_calloc(sizeof(char *), (count_word(s, c) + 1), track);
	while (++j < size && s[i])
	{
		while ((s[i] == c && s[i] && !state_checker((char *)s, 0, i)))
			i++;
		newstring[j] = gc_substr(track, s, i, find_next_idx((char *)s, i) - i);
		i += find_next_idx((char *)s, i) - i;
	}
	newstring[j] = 0;
	return (newstring);
}
