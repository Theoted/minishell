/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:08:44 by rmattheo          #+#    #+#             */
/*   Updated: 2022/04/07 14:12:19 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	close_all_file(t_commands *c)
{
	int	i;

	i = 0;
	while (c[++i].stop)
	{
		if (c[i].infile)
			if(close (c[i].infile) == -1)
				exit(1);
		if (c[i].outfile)
			if(close (c[i].outfile) == -1)
				exit(1);
	}
}

void	e_heredoc_pipe(t_data_p *data, t_commands *c, int i)
{
	int	pfd_heredoc[2];
	pipe (pfd_heredoc);
	c[i].pipe_heredoc0 = pfd_heredoc[0];
	c[i].pipe_heredoc1 = pfd_heredoc[1];
}

void	open_all_pipe(t_data_p *data, t_commands *c)
{
	int	i;
	
	i = -1;
	int	pfd[2];
	while (++i <= data->pipes_nb)
	{
		pipe(pfd);
		c[i].next_pfd1 = pfd[1];
		c[i].next_pfd0 = pfd[0];
		if (i >= 1)
		{
			c[i].prev_pfd1 = c[i - 1].next_pfd1;
			c[i].prev_pfd0 = c[i - 1].next_pfd0;
		}
	}
	
}

void	close_all_pipe(t_commands *c)
{
	int	i;

	i = -1;
	while(!c[++i].stop)
	{
		printf("c[i].pfdnext0 == %i\n", c[i].next_pfd0);
		printf("c[i].pfdnext1 == %i\n", c[i].next_pfd1);
		if (c[i].next_pfd0)
			if(close (c[i].next_pfd0))
				exit(1);
		if (c[i].next_pfd1)
			if(close (c[i].next_pfd1))
				exit(1);
		if (c[i].prev_pfd0)
			if(close (c[i].prev_pfd0))
				exit(1);
		if (c[i].prev_pfd1)
			if(close (c[i].prev_pfd1))
				exit(1);
		if (c[i].pipe_heredoc0)
			if(close (c[i].pipe_heredoc0))
				exit(1);
		if (c[i].pipe_heredoc1)
			if(close (c[i].pipe_heredoc1))
				exit(1);
	}
}