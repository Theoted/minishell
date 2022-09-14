/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:38:41 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/12 14:48:53 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ----------------------- CHECK HERE DOC AND GET DEL -----------------------
int	check_heredoc(char *arg, t_data_p *data, int idx)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '<' && arg[i + 1] == '<')
		{
			if (arg[i + 2] == '<')
			{
				printf("Chevrons: Synthax error\n");
				gc_free_all(&data->track);
				return (1);
			}
			get_heredoc_del(arg, i + 2, data);
			ft_here_doc(data, idx);
		}
		i++;
	}
	return (0);
}

int	get_heredoc_del(char *arg, int i, t_data_p *data)
{
	int		j;
	int		quote;

	quote = 0;
	data->hd_data.expend_var = 1;
	while (arg[i] == ' ' && arg[i])
		i++;
	j = i;
	while (arg[i] != ' ' && arg[i] != '<' && arg[i])
	{
		if ((arg[i] == '\"' || arg[i] == '\''))
		{
			data->hd_data.expend_var = 0;
			quote = 1;
		}
		i++;
	}
	data->hd_data.here_doc_del = gc_substr(&data->track, arg, j, (i - j));
	if (quote != 0)
		format_del(data->hd_data.here_doc_del, data);
	return (0);
}

// Cette fonction permet de mettre le delimiteur au bon format
// par rapport aux guillemets 
int	format_del(char *del, t_data_p *data)
{
	int		i;
	int		j;
	char	quote;
	char	*new_del;

	i = -1;
	j = 0;
	quote = 0;
	new_del = gc_calloc(sizeof(char), (ft_strlen(del) + 1), &data->track);
	while (del[++i])
	{
		if ((del[i] == '\'' || del[i] == '\"') && quote == 0)
			quote = del[i++];
		if (del[i] == quote && quote != 0 && del[i++])
			quote = 0;
		if ((del[i] == '\'' || del[i] == '\"') && quote == 0)
			continue ;
		else
			new_del[j] = del[i];
		j++;
	}
	data->hd_data.here_doc_del = gc_strdup(&data->track, new_del);
	return (0);
}

int	set_id_after_env(char *buffer, int i)
{
	while (buffer[++i])
	{
		if (buffer[i] == ' ' || !ft_isalnum(buffer[i]))
			return (i);
	}
	return (i);
}
