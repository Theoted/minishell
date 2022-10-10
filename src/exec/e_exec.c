/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/10/10 11:46:32 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_fork(t_data *data, t_tokens *c, int i)
{
	c[i].pid = fork();
	if (c[i].pid == -1)
	{
		write(2, "fork: Resource temporarily unavailable\n", 40);
		g_status = 1;
		return (0);
	}
	else if (!c[i].pid)
	{
		sig_child();
		if (e_child(data, &c[i], i) == -1)
			return (0);
	}
	else
		dup_fd_in_pipe(c, i);
	return (1);
}

void	ft_waitpid(t_tokens *c, int i)
{
	int	status;

	waitpid(c[i].pid, &status, 0);
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
			if (token->fd_out != 1 && token->fd_out != 0)
				close(token->fd_out);
		}
	}
	i = -1;
	while (token[++i].stop == 0)
		ft_waitpid(token, i);
}
