/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 09:42:47 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 17:40:48 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_n(char *arg, int i)
{
	while (arg[++i] && arg[i] != '-')
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			if (arg[i + 1] == arg[i])
				i++;
			else if (arg[i + 1] == '-')
			{
				i++;
				break ;
			}
			else
				return (0);
		}
	}
	if (arg[i] == '-')
	{
		if (arg[i + 1] != 'n')
			return (0);
		while (arg[++i])
			if (arg[i] != 'n' && arg[i] != '\'' && arg[i] != '\"')
				return (0);
		return (1);
	}
	return (0);
}

int	arg_vec_len(t_data *data, int idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->commands[idx].args_vec[++i])
	{
		j++;
	}
	return (j);
}

// Cette fonction retourne l'id de la prochaine quote identique
// A utiliser lorsqu'on rencontre une quote alors que nous ne somme dans
// Aucune quote
int	next_quote_id(char *arg, char quote, int i)
{
	i++;
	while (arg[i])
	{
		if (arg[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

// Cette fonction retourne l'id de la fin du mot ou jusqu'a la prochaine
// quote sachant que nous ne somme pas dans une quote
int	word_end_id(char *arg, int i)
{
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			return (i);
		i++;
	}
	return (i);
}

int	check_dol_int(char *arg, int *i)
{
	if (arg[*i] == '$' && arg[(*i) + 1] && arg[(*i) + 1] == '?')
	{
		(*i)++;
		return (1);
	}
	return (0);
}
