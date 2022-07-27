/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:39:30 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/27 10:40:14 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction permet de savoir si on est dans des guillemets
int	state_checker(char *str, int start, int len)
{
	int	i;
	int	quote;

	i = start;
	quote = 0;
	while (str[i] && i < len)
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote && quote != 0)
			quote = 0;
		i++;
	}
	return (quote);
}

// Cette fonction permet de savoir le dernier infile dans l'ordre
// < ou <<
int	last_in_redir(char *arg)
{
	int	check;
	int	i;

	check = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '<')
		{
			if (arg[i + 1] == '<')
			{
				check = 2;
				i++;
			}
			else
				check = 1;
		}
	}
	return (check);
}
