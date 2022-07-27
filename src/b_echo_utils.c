/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 09:42:47 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/27 10:46:13 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Retourne 1 si le premier char de l'argument a un tiret et un 'n' 
// ou plus sinon retourne 0
int	check_n(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
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
	i++;
	while (arg[i])
	{
		if (arg[i] == quote)
		{
			e_d->quote = 0;
			return (i);
		}
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
