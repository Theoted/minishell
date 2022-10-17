/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:12:29 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 15:04:15 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Cette fonction est la fonction principale de parsing de l'argument,
// pour trouver la commande outre les <, <<, >, >> 
char	*skip_in_out_hd(char *arg, t_data *data, int i)
{
	char	*cmd;

	cmd = NULL;
	while (arg[++i])
	{
		while (arg[i] == ' ')
			i++;
		if (arg[i] == '<' && !state_checker(arg, 0, i))
			skip_in_hd(arg, &i);
		else if (arg[i] == '>' && !state_checker(arg, 0, i))
			skip_out(arg, &i);
		else
		{
			if (!cmd)
				cmd = get_cmd(arg, i, data);
			else if (cmd)
				cmd = gc_strjoin(&data->track,
						gc_strjoin(&data->track, cmd, " "),
						get_cmd(arg, i, data));
			i += ft_strlen(get_cmd(arg, i, data)) - 1;
		}
		if (!arg[i])
			return (cmd);
	}
	return (cmd);
}

// Cette fonction skip les < et <<
void	skip_in_hd(char *arg, int *i)
{
	(*i)++;
	if (arg[*i] == '<')
		(*i)++;
	while (arg[*i] == ' ')
		(*i)++;
	while (arg[*i] != ' ' && arg[*i] != '>' && arg[*i] != '<' && arg[*i])
		(*i)++;
	if (arg[*i] == '<' || arg[*i] == '>')
		(*i)--;
}

// Cette fonction skip les > et >>
void	skip_out(char *arg, int *i)
{
	if (arg[*i + 1] == '>')
		(*i)++;
	(*i)++;
	while (arg[*i] == ' ')
		(*i)++;
	while (arg[*i] != ' ' && arg[*i] != '>' && arg[*i] != '<' && arg[*i])
		(*i)++;
	if (arg[*i] == '<' || arg[*i] == '>')
		(*i)--;
}

// Cette fonction recupere la commande
char	*get_cmd(char *arg, int i, t_data *data)
{
	int	j;

	j = 0;
	while (arg[i + j])
	{
		if ((arg[i + j] == '<' || arg[i + j] == '>' || arg[i + j] == ' ')
			&& !state_checker(arg, 0, i + j))
			break ;
		j++;
	}
	return (gc_substr(&data->track, arg, i, j));
}
