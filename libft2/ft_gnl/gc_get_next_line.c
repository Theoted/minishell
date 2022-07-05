/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:08:28 by tdeville          #+#    #+#             */
/*   Updated: 2022/06/08 10:34:17 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/gc.h"

static void	get_line(t_track **track, char **line, int fd, char *buffer)
{
	int		r;

	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0)
	{
		buffer[r] = '\0';
		if (!*line)
			*line = gc_substr(track, buffer, 0, r);
		else
		{
			*line = gc_strjoin(track, *line, buffer);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		r = read(fd, buffer, BUFFER_SIZE);
	}
}

static char	*parse_line(t_track **track, char **line)
{
	int		j;
	char	*tmp;

	if (!*line)
		return (NULL);
	if (!ft_strchr(*line, '\n'))
	{
		if (*line[0] == '\0')
		{
			gc_free_malloc(track, *(void **)line);
			*line = NULL;
			return (NULL);
		}
		tmp = gc_substr(track, *line, 0, ft_strlen(*line));
		*line = NULL;
		return (tmp);
	}
	j = ft_strlen(ft_strchr(*line, '\n'));
	tmp = gc_substr(track, *line, 0, ft_strlen(*line) - j + 1);
	*line = gc_substr(track, ft_strchr(*line, '\n'), 1, j);
	return (tmp);
}

char	*gc_get_next_line(t_track **track, int fd)
{
	static char	*line;
	char		*str;
	char		buffer[BUFFER_SIZE + 1];

	if (read(fd, buffer, 0) == -1 || BUFFER_SIZE < 0)
		return (NULL);
	if (!(ft_strchr(line, '\n')))
		get_line(track, &line, fd, buffer);
	str = parse_line(track, &line);
	return (str);
}
