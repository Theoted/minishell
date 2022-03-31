/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:08:44 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/31 19:09:55 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	open_all_pipe(t_data_p *data, t_commands *c)
{
	int	i;
	
	i = -1;
	int	pfd[2];
	data->pip = pfd; 
	while (++i <= data->pipes_nb)
	{
		pipe(pfd);
		c[i].next_pfd1 = pfd[1];
		c[i].next_pfd0 = pfd[0];
		if (i > 1)
		{
			c[i].last_pfd1 = c[i - 1].next_pfd1;
			c[i].last_pfd0 = c[i - 1].next_pfd0;
		}
	}
	
}

void	close_all_pipe(t_commands *c)
{
	int	i;
	
	i = -1;
	while(!c[++i].stop)
	{
		if (c[i].next_pfd0)
		{
			if(close (c[i].next_pfd0))
				return (-1);
		}
		if (c[i].next_pfd1)
		{
			if(close (c[i].next_pfd1))
				return (-1);
		}
	}
}
