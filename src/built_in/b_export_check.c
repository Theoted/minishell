/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:57:10 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 15:50:59 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	export_check_idtf(char *arg)
{
	int	i;
	int	egal;

	egal = contains_equal(arg);
	i = 0;
	if (arg[i] == '_' || ft_isalpha(arg[i]))
	{
		while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
			i++;
		if (egal)
		{
			if (i < next_equal(arg))
				return (export_error_arg(arg));
		}
		else
		{
			if ((size_t)i < ft_strlen(arg))
				return (export_error_arg(arg));
		}
	}
	else
		return (export_error_arg(arg));
	return (0);
}
