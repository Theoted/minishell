/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:08:33 by pat               #+#    #+#             */
/*   Updated: 2022/09/30 14:47:31 by rmattheo         ###   ########lyon.fr   */
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

void	dup_fd_in_pipe(t_commands *c, int i)
{
	close(c[i].pfd[1]);
	if (c[i].fd_in)
		close(c[i].fd_in);
	if (!c[i + 1].stop)
		c[i + 1].fd_in = dup(c->pfd[0]);
	close(c[i].pfd[0]);
}

void	check_path(t_data_p *d, t_commands *c)
{
	int	i;

	i = -1;
	if (access(c->args_vec[0], X_OK)
		&& c->args_vec[0])
		c->cmd_path = gc_strdup(&d->track, c->args_vec[0]);
	d->cmd_slash = gc_strjoin(&d->track, "/", c->args_vec[0]);
	if (d->env_path)
	{
		while (d->env_path[++i])
		{
			c->cmd_path = gc_strjoin(&d->track,
					d->env_path[i], d->cmd_slash);
			if (!access(c->args_vec[0], X_OK))
			{
				c->cmd_path = c->args_vec[0];
				return ;
			}
			if (!access(c->cmd_path, X_OK))
				return ;
			gc_free_malloc(&d->track, (void **)&c->cmd_path);
		}
	}
}

int check_built(char *built, int fd_out)
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
void	e_execve(t_data_p *d, t_commands *c, int idx)
{
	if (check_built(c->args_vec[0], c->fd_out))
		ft_exec_built_fork(d, c, idx);
	else
	{
		if (execve(c->cmd_path, c->args_vec, convert_envp(d, d->envp)) == -1)
		{
			write(2, c->args_vec[0],
				ft_strlen(c->args_vec[0]));
			write(2, ": command not found\n", 21);
			exit(0);
		}
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
	if (c->fd_out != 1)
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
