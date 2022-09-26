/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 08:33:28 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/26 11:29:22 by tdeville         ###   ########lyon.fr   */
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

	write(STDOUT_FILENO, "> ", 2);
	buffer = gc_get_next_line(&data->track, STDIN_FILENO);
	longest = del_len;
	if (ft_strlen(buffer) > (size_t)del_len)
		longest = (ft_strlen(buffer) - 1);
	if (!ft_strncmp(buffer,
			data->hd_data.here_doc_del, longest))
		return (1);
	here_doc_write(data, buffer, idx);
	gc_free_malloc(&data->track, (void **)&buffer);
	return (0);
}
