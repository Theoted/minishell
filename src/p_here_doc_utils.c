/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:28:03 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/17 14:02:33 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_of_env_vars(char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	check_var(char *var)
{
	if (var[0] == '$')
	{
		if (var[1] == '\'' || var[1] == '\"')
			return (1);
		return (0);
	}
	return (1);
}

char	*check_bsn_buffer(t_data_p *data, char *new_buffer)
{
	int		len;
	
	len = ft_strlen(new_buffer);
	if (new_buffer[len - 1] != '\n')
	{
		new_buffer = gc_strjoin(&data->track, new_buffer, "\n");
		return (new_buffer);
	}
	return (new_buffer);
}

char	*trim_last_bsn(t_data_p *data, char *here_doc_content)
{
	int		len;

	len = ft_strlen(here_doc_content);
	if (here_doc_content[len - 1] == '\n')
	{
		here_doc_content = gc_substr(&data->track, here_doc_content, 0, len - 1);
		return (here_doc_content);
	}
	return (here_doc_content);
}
