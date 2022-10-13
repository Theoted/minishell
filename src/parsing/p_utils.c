/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:52:41 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/13 01:16:01 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Cette fonction permet de recuperer le type de file (type),
// de mettre l'index dans l'argument au debut du nom du file
// et de recuperer l'index de la fin du mot pour pouvoir le
// substr
int	get_file(char *arg, int *start, int *type)
{
	int	i;

	i = 0;
	if (arg[(*start)] == '<')
		if (arg[(*start) + 1] == '<')
			return (idx_after_hd(arg, start));
	(*type) = 1;
	if (arg[(*start)] == '>')
	{
		if (arg[(*start) + 1] == '>')
		{
			(*type) = 3;
			(*start)++;
		}
		else
			(*type) = 2;
	}
	(*start)++;
	while (arg[(*start)] == ' ' && arg[(*start)])
		(*start)++;
	while ((arg[(*start) + i] != ' ' && arg[(*start) + i] != '<'
			&& arg[(*start) + i] != '>') && arg[(*start) + i])
		i++;
	return (i);
}

// Cette fonction permet de set l'id apres un here_doc
// pour pouvoir continuer a recuperer les <, >, >>
int	idx_after_hd(char *arg, int *start)
{
	int	i;

	i = 0;
	(*start)++;
	while (arg[(*start)] == ' ' && arg[(*start)])
		(*start)++;
	while ((arg[(*start) + i] != ' ' && arg[(*start) + i] != '<'
			&& arg[(*start) + i] != '>') && arg[(*start) + i])
		i++;
	return (-1);
}

// cette fonction compte le nombre de <, >, >>
int	count_in_out_files(char *arg)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (arg[++i])
	{
		if (arg[i] == '<' && !state_checker(arg, 0, i))
		{
			if (arg[i + 1] == '<')
				i++;
			else
				count++;
		}
		else if (arg[i] == '>' && !state_checker(arg, 0, i))
		{
			if (arg[i + 1] == '>')
				i++;
			count++;
		}
	}
	return (count);
}

// Cette fonction met les env var dans
// chaque case du tabl de struct command
void	fill_envp_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->commands[i].stop == 0)
	{
		data->commands[i].envp = data->env_vars;
		i++;
	}
}

// Cette fonction est celle qui va remplire le tabl de structure t_files
// qui se trouve dans chaque t_tokens
int	get_in_out_files(char *arg, t_data *data, int idx)
{
	int	i;
	int	j;
	int	len;
	int	in_type;

	get_in_out_init(&i, &j, &in_type);
	data->commands[idx].files = gc_calloc(count_in_out_files(arg) + 1,
			sizeof(t_files), &data->track);
	data->commands[idx].files[count_in_out_files(arg)].stop = 1;
	while (arg[++i])
	{
		if ((arg[i] == '<' || arg[i] == '>') && !state_checker(arg, 0, i))
		{
			len = get_file(arg, &i, &in_type);
			if (len != -1)
			{
				data->commands[idx].files[++j].file_name
					= gc_substr(&data->track, arg, i, len);
				data->commands[idx].files[j].type = in_type;
				data->commands[idx].files[j].file_name = remove_quotes(data,
						data->commands[idx].files[j].file_name);
				if (!data->commands[idx].files[j].file_name)
					return (-1);
			}
		}
		if (!arg[i])
			return(0);
	}
	return (0);
}
