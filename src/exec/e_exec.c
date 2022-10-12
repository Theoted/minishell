/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/10/12 20:45:53 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_fork(t_data *data, t_tokens *token, int i)
{
	token[i].pid = fork();
	if (token[i].pid == -1)
	{
		write(2, "fork: Resource temporarily unavailable\n", 40);
		g_status = 1;
		return (0);
	}
	else if (!token[i].pid)
	{
		sig_child();
		if (e_child(data, &token[i], i) == -1)
			return (0);
	}
	else
		dup_fd_in_pipe(token, i);
	return (1);
}

void	ft_waitpid(t_tokens *token, int i)
{
	int	status;

	waitpid(token[i].pid, &status, 0);
	if (!WIFSIGNALED(status))
		g_status = WEXITSTATUS(status);
	else if (g_status == 131)
	{
		write(1, "Quit: 3\n", 8);
	}
	else if (g_status == 130)
	{
		write(1, "\n", 1);
	}
}

/* Parcours le tableau de commande et fork 
	apres chaque commandes pour l'executer et creation du pipe */
void	e_exec(t_data *data, t_tokens *token)
{
	int	i;

	i = -1;
	while (token[++i].stop == 0)
	{
		if (token[i + 1].stop)
			token[i].fd_out = 1;
		pipe(token[i].pfd);
		if (open_files(&token[i]))
		{
			if (!ft_exec_built_nofork(data, token[i], i))
				if (!ft_fork(data, token, i))
					return ;
			if (token[i].fd_out != 1 && token[i].fd_out != 0)
				close(token[i].fd_out);
		}
		else
			dup_fd_in_pipe(token, i);
	}
	i = -1;
	while (token[++i].stop == 0)
		ft_waitpid(token, i);
}
