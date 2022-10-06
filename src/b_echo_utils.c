/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 09:42:47 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/05 20:40:32 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Retourne 1 si le premier char de l'argument a un tiret et un 'n' 
// ou plus sinon retourne 0
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
		while (arg[++i])
			if (arg[i] != 'n' && arg[i] != '\'' && arg[i] != '\"')
				return (0);
		return (1);
	}
	return (0);
}

int	arg_vec_len(t_data_p *data, int idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->commands[idx].args_vec[++i])
		j++;
	return (j);
}

// Cette fonction retourne l'id de la prochaine quote identique
// A utiliser lorsqu'on rencontre une quote alors que nous ne somme dans
// Aucune quote
int	next_quote_id(char *arg, char quote, int i, t_echo *e_d)
{
	//TODO : enlever e_d des params
	(void) e_d;
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
