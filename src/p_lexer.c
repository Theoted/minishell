/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:17:25 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/25 14:28:14 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			if (!pipe_check(str, i))
				count++;
		i++;
	}
	return (count);
}

int	create_arg(char *str, int i, t_data_p *data, int bad_pipe)
{
	int		j;
	char	*arg;

	j = i;
	while (str[--j] != '|' && str[j] && j)
	{
		while (str[j - 1] == '|' && bad_pipe > 0)
		{
			j--;
			bad_pipe--;
		}
	}
	if (str[j] == '|')
		j++;
	arg = gc_substr(&data->track, str, j, i - j);
	if (!arg)
		return (1);
	data->args[data->args_create] = gc_strtrim(&data->track, arg, " ");
	if (!data->args[data->args_create])
		return (1);
	data->args_create++;
	return (0);
}

// Fonction qui split l'argument principale via les |
int	split_args(char *arg, t_data_p *data)
{
	int		i;
	int		bad_pipe;

	i = 0;
	bad_pipe = 0;
	while (arg[i])
	{
		if (arg[i] == '|')
		{
			if (!pipe_check(arg, i))
			{
				if (create_arg(arg, i, data, bad_pipe) != 0)
					return (1);
				bad_pipe = 0;
			}
			else
				bad_pipe++;
		}
		i++;
	}
	if (create_arg(arg, i, data, bad_pipe) != 0)
		return (1);
	data->args[data->args_create] = 0;
	return (0);
}

int	lexer(char *arg, t_data_p *data)
{
	int	i;

	i = 0;
	data->pipes_nb = count_pipes(arg);
	data->args_create = 0;
	data->args = gc_calloc(sizeof(char *), (data->pipes_nb + 2), &data->track);
	data->commands = gc_calloc(sizeof(t_commands), (data->pipes_nb + 2), &data->track);
	data->commands[data->pipes_nb + 1].stop = 1;
	fill_envp_cmd(data);
	if (synthax_checker(arg)) 
	{
		printf("Synthax error\n");
		return (1);
	}
	if (split_args(arg, data) != 0)
		return (1);
	while (data->args[i])
	{
		data->commands[i].last_in_type = last_in_redir(data->args[i]);
		get_in_out_files(data->args[i], data, i);
		if (check_heredoc(data->args[i], data, i))
			return (1);
		get_cmd_in_arg(data->args[i], data, i);
		// check_arg_vars(data->args[i], data);
		i++;
	}
	return (0);
}

