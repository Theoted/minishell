/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:08:33 by pat               #+#    #+#             */
/*   Updated: 2022/10/06 08:07:42 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_fd_in_pipe(t_commands *c, int i)
{
	close(c[i].pfd[1]);
	if (c[i].fd_in)
		close(c[i].fd_in);
	if (!c[i + 1].stop)
		c[i + 1].fd_in = dup(c->pfd[0]);
	close(c[i].pfd[0]);
}

void	e_execve(t_data_p *d, t_commands *c, int idx)
{
	if (!c->args_vec)
		exit(0);
	if (check_built(c->args_vec[0], c->fd_out))
		ft_exec_built_fork(d, c, idx);
	else
	{
		if (execve(c->cmd_path, c->args_vec, convert_envp(d, d->envp)) == -1)
			execve_error(c->args_vec[0]);
	}
}

void	e_heredoc(t_commands *c)
{
	int	pipe_heredoc[2];

	pipe(pipe_heredoc);
	write(pipe_heredoc[1], c->here_doc, ft_strlen(c->here_doc));
	close(pipe_heredoc[1]);
	dup2(pipe_heredoc[0], STDIN_FILENO);
	close(pipe_heredoc[0]);
}

/* execution de la commande dans le child */
int	e_child(t_data_p *d, t_commands *c, int idx)
{
	if (c->fd_out != 1 && c->fd_out != 0)
	{
		dup2(c->fd_out, STDOUT_FILENO);
		close(c->fd_out);
	}
	if (c->last_in_type == HEREDOC_TYPE)
		e_heredoc(c);
	if (c->last_in_type != HEREDOC_TYPE)
		dup2(c->fd_in, STDIN_FILENO);
	if (c->fd_in)
		close(c->fd_in);
	close(c->pfd[0]);
	if (c->fd_out == 0)
		dup2(c->pfd[1], STDOUT_FILENO);
	close(c->pfd[1]);
	check_path(d, c);
	e_execve(d, c, idx);
	return (1);
}
