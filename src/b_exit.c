/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:31:14 by theodeville       #+#    #+#             */
/*   Updated: 2022/09/27 14:03:45 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	b_exit(t_data_p *d, int idx)
{
	if (!strncmp_len("exit", d->commands[idx].args_vec[0]))
	{
		if (d->commands[idx].args_vec[1])
		{
			g_status = atoi(d->commands[idx].args_vec[1]);
		}
		write(1, "exit\n", 5);
		exit(g_status);
	}
	return (0);
}
