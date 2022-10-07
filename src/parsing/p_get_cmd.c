/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:12:29 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/07 01:27:39 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Cette fonction est la fonction principale de parsing de l'argument,
// pour trouver la commande outre les <, <<, >, >> 
char	*skip_in_out_hd(char *arg, t_data *data)
{
	int		i;
	char	*cmd;

	i = -1;
	cmd = NULL;
	while (arg[++i])
	{
		if (arg[i] == ' ' && !state_checker(arg, 0, i))
			skip_spaces(arg, &i);
		else if (arg[i] == '<' && !state_checker(arg, 0, i))
			skip_in_hd(arg, &i);
		else if (arg[i] == '>' && !state_checker(arg, 0, i))
			skip_out(arg, &i);
		else
		{
			cmd = get_cmd(arg, i, data);
			break ;
		}
		if (!arg[i])
			break ;
	}
	return (cmd);
}

// Cette fonction skip les < et <<
void	skip_in_hd(char *arg, int *i)
{
	if (arg[*i + 1] == '<')
		(*i)++;
	(*i)++;
	skip_spaces(arg, i);
	while (arg[*i] != ' ' && arg[*i] != '>' && arg[*i])
		(*i)++;
}

// Cette fonction skip les > et >>
void	skip_out(char *arg, int *i)
{
	if (arg[*i + 1] == '>')
		(*i)++;
	(*i)++;
	skip_spaces(arg, i);
	while (arg[*i] != ' ' && arg[*i] != '<' && arg[*i])
		(*i)++;
}

// Cette fonction skip les espaces
void	skip_spaces(char *arg, int *i)
{
	while (arg[*i] == ' ' && arg[*i] && !state_checker(arg, 0, *i))
		(*i)++;
}

// Cette fonction recupere la commande
char	*get_cmd(char *arg, int i, t_data *data)
{
	int	j;

	j = 0;
	while (arg[i + j])
	{
		if ((arg[i + j] == '<' || arg[i + j] == '>')
			&& !state_checker(arg, 0, i + j))
			break ;
		j++;
	}
	return (gc_substr(&data->track, arg, i, j));
}