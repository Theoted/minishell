/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:08:44 by rmattheo          #+#    #+#             */
/*   Updated: 2022/03/31 20:32:07 by rmattheo         ###   ########lyon.fr   */
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
#include "../includes/exec.h"

void	e_cmd_cmd(t_data_p *data, t_commands c)
{
	if (close(c.last_pfd1) == -1)
		exit(1);
	if (close(c.next_pfd0) == -1)
		exit(1);
	if (dup2(c.last_pfd0, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(c.next_pfd1, STDOUT_FILENO) == -1)
		exit(1);
	if (close(c.last_pfd0) == -1)
		exit(1);
	if (close(c.next_pfd1) == -1)
		exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
}

void	e_cmd_outfile(t_data_p *data, t_commands c)
{
	
	if (close(c.last_pfd1) == -1)
		exit(1);
	if (dup2(c.last_pfd0, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(c.outfile, STDOUT_FILENO) == -1)
		exit(1);
	if (close(c.last_pfd0) == -1)
		exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
	if (close(c.outfile) == -1)
		exit(1);
}

void	e_infile_heredoc_cmd(t_data_p *data, t_commands c)
{
	if (close(c.next_pfd0) == -1)
		exit(1);
	if (c.here_doc)
	{
		if (write(c.next_pfd1, c.here_doc, ft_strlen(c.here_doc)) == -1)
			exit(1);
		if (dup2(c.next_pfd1, STDIN_FILENO) == -1)
			exit(1);
	}
	else if (c.infile)
		if (dup2(c.infile, STDIN_FILENO) == -1)
			exit(1);
	if (dup2(c.next_pfd1, STDOUT_FILENO) == -1)
		exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
	if (c.infile)
		if (close(c.infile) == -1)
			exit(1);
}

void	exec_heredoc_infile_cmd_outfile(t_data_p *data, t_commands c)
{
	if (close(c.last_pfd1) == -1)
		exit(1);
	if (dup2(c.last_pfd0, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(c.outfile, STDOUT_FILENO) == -1)
		exit(1);
	if (close(c.last_pfd0) == -1)
		exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
	if (close(c.outfile) == -1)
		exit(1);
}

void	e_exec(t_data_p *data, t_commands *c)
{
	int	i;

	i = -1;
	open_all_pipe(data, c);
	while ((c[++i]).stop)
	{
		if((c[i].pid = fork()) == -1)
			gc_free_all(&data->track);
		if (c[i].pid == 0)
		{
			if ((c->here_doc || c-> infile) && c->outfile)
				e_infile_heredoc_cmd_outfile(data, c[i]);
			else if (c->infile || c->here_doc)
				e_heredoc_infile_cmd(data, c[i]);
			else if (c->outfile)
				e_cmd_outfile(data, c[i]);
			else
				e_cmd_cmd(data, c[i]);
		}
	}
	close_all_pipe(c);
	i = -1;
	while (c[++i].stop)
		waitpid(c[i].pid, NULL, 0);
}
