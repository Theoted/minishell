/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:57:10 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/13 12:06:17 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_check_idtf(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
		return (export_error_arg(arg));
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (export_error_arg(arg));
	while (arg[++i])
		if (!ft_isalnum(arg[i]) && arg[i] != '-')
			return(export_error_arg(arg));
	return (0);
}
