/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:57:10 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/14 20:24:25 by theodeville      ###   ########.fr       */
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

	i = 0;
	if (arg[i] == '_' || ft_isalpha(arg[i]))
	{
		while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
			i++;
		if (contains_equal(arg))
		{
			if (i < next_equal(arg))
				return(export_error_arg(arg));
		}
		else
		{
			if ((size_t)i < ft_strlen(arg))
				return(export_error_arg(arg));
		}
	}
	else
		return(export_error_arg(arg));
	return (0);
}
