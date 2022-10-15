/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_built2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:59:57 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/15 01:22:37 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_built_no_fork(char *built)
{
	if (!strncmp_ncs(built, "exit"))
		return (1);
	if (!strncmp_ncs(built, "env"))
		return (1);
	if (!strncmp_ncs(built, "unset"))
		return (1);
	if (!strncmp_ncs(built, "export"))
		return (1);
	return (0);
}


int	check_built(char *built, int fd_out)
{
	(void)fd_out;
	if (!strncmp_ncs(built, "env"))
		return (1);
	if (!strncmp_ncs(built, "pwd"))
		return (1);
	if (!strncmp_ncs(built, "echo"))
		return (1);
	if (!strncmp_ncs(built, "export"))
		return (1);
	return (0);
}
