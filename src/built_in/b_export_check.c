/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:57:10 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/14 05:04:47 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_check_idtf(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '_' || ft_isalpha(arg[i]))
	{
		while ((ft_isalnum(arg[i]) || arg[i] == '_') && arg[i])
		{
			i++;
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=' && arg[i])
			return(export_error_arg(arg));
		if (arg[i] == '=')
			i++;
		while (ft_isalnum(arg[i]) || arg[i] == '_' || arg[i] == '=')
		{
			i++;
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=' && arg[i])
			return(export_error_arg(arg));
	}
	else
		return(export_error_arg(arg));
	return (0);
}
