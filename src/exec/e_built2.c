/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_built2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:59:57 by rmattheo          #+#    #+#             */
/*   Updated: 2022/10/10 14:58:23 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_built(char *built, int fd_out)
{
	if (!strncmp_ncs(built, "env"))
		return (1);
	if (!strncmp_ncs(built, "pwd"))
		return (1);
	if (!strncmp_ncs(built, "echo"))
		return (1);
	if (!strncmp_ncs(built, "export") && fd_out)
		return (1);
	return (0);
}
