/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:18:37 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/13 11:49:36 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*echo_trim_bs(char *arg, int *i, t_data_p *data)
{
	char	*new;
	int		count;
	int		j;

	new = "";
	count = 0;
	j = -1;
	while (arg[*i] && arg[*i] == '\\')
	{
		(*i)++;
		count++;
	}
	(*i)--;
	new = gc_calloc(count / 2, sizeof(char), &data->track);
	while (++j < count / 2)
		new[j] = '\\';
	return (new);
}

char	*echo_parse_bs(char *arg, t_data_p *data)
{
	char	*new;
	char	*tmp;
	int		i;
	int		j;

	new = NULL;
	tmp = NULL;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\\')
			tmp = echo_trim_bs(arg, &i, data);
		else
		{
			j = i;
			while (arg[i] != '\\' && arg[i])
				i++;
			tmp = gc_substr(&data->track, arg, j, (i - j));
			i--;
		}
		if (!new)
			new = gc_strdup(&data->track, tmp);
		else
			new = gc_strjoin(&data->track, new, tmp);
	}
	return (new);
}
