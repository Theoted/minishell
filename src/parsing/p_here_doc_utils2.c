/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 08:33:28 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/07 01:10:57 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pipe_content(int fd, t_data *data)
{
	char	get_pipe_content[3];
	char	*tmp;
	int		r;

	r = read(fd, get_pipe_content, 2);
	get_pipe_content[2] = 0;
	tmp = NULL;
	if (r)
		tmp = gc_strdup(&data->track, get_pipe_content);
	while (r)
	{
		r = read(fd, get_pipe_content, 2);
		get_pipe_content[r] = 0;
		tmp = gc_strjoin(&data->track, tmp, get_pipe_content);
	}
	if (tmp)
		return (gc_strdup(&data->track, tmp));
	else
		return (NULL);
}

int	hd_loop(t_data *data, int idx)
{
	char	*buffer;

	buffer = readline("> ");
	if (!buffer)
		return (1);
	buffer = gc_strjoin(&data->track, buffer, "\n");
	if (!strncmp_len(buffer,
			gc_strjoin(&data->track, data->hd_data.here_doc_del, "\n")))
		return (1);
	here_doc_write(data, buffer, idx);
	gc_free_malloc(&data->track, (void **)&buffer);
	return (0);
}
