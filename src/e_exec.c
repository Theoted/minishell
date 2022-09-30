/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/09/30 12:44:38 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ft_waitpid(t_commands *c, int i)
{
	int	status;

	waitpid(c[i].pid, &status, 0);
	if (!WIFSIGNALED(status))
		g_status = WEXITSTATUS(status);
}

/* Parcours le tableau de commande et fork 
	apres chaque commandes pour l'executer et creation du pipe */
void	e_exec(t_data_p *d, t_commands *c)
{
	int	i;

	i = -1;
	while (c[++i].stop == 0)
	{
		if (c[i + 1].stop)
			c[i].fd_out = 1;
		pipe(c[i].pfd);
		open_files(&c[i]);
		if (!ft_exec_built_nofork(d, &c[i], i))
		{
			c[i].pid = fork();
			if (!c[i].pid)
			{
				sig_child();
				signal(SIGINT, sig_handler_child);
				if (e_child(d, &c[i], i) == -1)
					return ;
			}
			else
				dup_fd_in_pipe(c, i);
		}
	}
	i = -1;
	while (c[++i].stop == 0)
		ft_waitpid(&c[i], i);
}
