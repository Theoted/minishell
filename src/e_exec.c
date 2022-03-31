/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/03/31 11:16:22 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_pipe_heredoc
_cmd_outfile(t_data_p *data, t_commands *c)
{
	if (dup2(c->fd_infile, STDIN_FILENO) == -1)
		gc_free_all(&data->track);
	if (dup2(c -> fd_outfile, STDOUT_FILENO) == -1)
		gc_free_all(&data->track);
	if (close(c->fd_infile) == -1);
		gc_free_all(&data->track);
	if (close(c->fd_outfile) == -1);
		gc_free_all(&data->track);
	if (execve (c->cmd_path, c->cmd, c->envp) == -1)
	{
		gc_free_all(&data->track);
		exit(1);
	}
}

void	ft_pipe_infile_cmd_outfile(t_data_p *data, t_commands *c)
{
	if (dup2(c->fd_infile, STDIN_FILENO) == -1)
		gc_free_all(&data->track);
	if (dup2(c -> fd_outfile, STDOUT_FILENO) == -1)
		gc_free_all(&data->track);
	if (close(c->fd_infile) == -1);
		gc_free_all(&data->track);
	if (close(c->fd_outfile) == -1);
		gc_free_all(&data->track);
	if (execve (c->cmd_path, c->cmd, c->envp) == -1)
	{
		gc_free_all(&data->track);
		exit(1);
	}
}

void	e_exec(t_data_p *data, t_commands *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].stop)
	{
		if((cmd[i].pid = fork()) == -1)
			gc_free_all(&data->track);
		if (cmd[i].pid == 0)
		{
			if (cmd->here_doc)
			else

		}
		close(d->lst->prev->command->pfdin);
	}
	i = -1;
	while (++i < d->main.argc - 3)
		waitpid(pid[i], NULL, 0);
}