/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_built2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:59:57 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/05 20:20:38 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_strcmp(char *arg, char *built)
{
	int	i;

	i = -1;
	if (ft_strlen(arg) != ft_strlen(built))
		return (0);
	while (arg[++i])
	{
		if (arg[i] != built[i])
			return (0);
	}
	return (1);
}

int	check_built(char *built, int fd_out)
{
	if (ft_strcmp(built, "env"))
		return (1);
	if (ft_strcmp(built, "pwd"))
		return (1);
	if (ft_strcmp(built, "echo"))
		return (1);
	if (ft_strcmp(built, "export") && fd_out)
		return (1);
	return (0);
}
