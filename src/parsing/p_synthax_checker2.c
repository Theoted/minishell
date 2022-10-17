/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_synthax_checker2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:06:50 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 17:23:55 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	check_heredoc2(char *arg, int i)
{
	int	check;

	check = 0;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]))
			check = 1;
		i++;
	}
	if (check)
		return (0);
	printf("synthax error: no del for here doc\n");
	g_status = 258;
	return (1);
}

int	check_space(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == '|')
	{
		g_status = 258;
		return (1);
	}
	if (arg[0] == ' ')
	{
		while (arg[++i])
		{
			if (ft_isalnum(arg[i]))
				return (0);
			if (arg[i] == '|')
			{
				g_status = 258;
				return (1);
			}
		}
	}
	return (0);
}
