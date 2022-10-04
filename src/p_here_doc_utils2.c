/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 08:33:28 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/03 17:15:55 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pipe_content(int fd, t_data_p *data)
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

int	hd_loop(t_data_p *data, int idx, int del_len)
{
	char	*buffer;
	int		longest;

	buffer = readline("> ");
	buffer = gc_strjoin(&data->track, buffer, "\n");
	if (!strncmp_len(buffer,
			gc_strjoin(&data->track, data->hd_data.here_doc_del, "\n")))
		return (1);
	here_doc_write(data, buffer, idx);
	gc_free_malloc(&data->track, (void **)&buffer);
	return (0);
}
