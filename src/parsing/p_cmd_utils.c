/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:50:02 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/10 15:40:41 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_2d_len(char **new)
{
	int	i;

	i = -1;
	while (new[++i])
		;
	return (i);
}

char	**new_args_vec(t_data *data, char **new, int idx, int i)
{
	char	**new_args;
	int		av_len;
	int		j;
	int		k;
	int		l;

	j = -1;
	k = -1;
	l = -1;
	av_len = double_arr_len(data->commands[idx].args_vec);
	new_args = gc_calloc(av_len + double_arr_len(new) + 1,
			sizeof(char *), &data->track);
	while (++j < av_len + double_arr_len(new))
	{
		if (j == i)
		{
			while (new[++k])
				new_args[j++] = gc_strdup(&data->track, new[k]);
		}
		else
			new_args[j] = gc_strdup(&data->track,
					data->commands[idx].args_vec[++l]);
	}
	return (new_args);
}

int	check_spaces2(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (0);
		if (arg[i] == ' ' && !state_checker(arg, 0, i))
			return (1);
	}
	return (0);
}

int	parse_space(t_data *data, char **args, int idx)
{
	int		i;
	char	**new;

	i = -1;
	new = NULL;
	while (args[++i])
	{
		if (check_spaces2(args[i]))
			new = new_args_vec(data,
					gc_split_spaces(&data->track, args[i], ' '), idx, i);
	}
	if (new)
		data->commands[idx].args_vec = new;
	return (0);
}
