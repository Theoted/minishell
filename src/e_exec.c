/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/04/14 12:12:42 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	e_heredoc(t_data_p *data, t_commands c)
{
	if (write(c.pipe_heredoc1, c.here_doc, ft_strlen(c.here_doc)) == -1)
		exit(1);
	if (close(c.pipe_heredoc1) == -1)
		exit(1);
	if (dup2(c.pipe_heredoc0, STDIN_FILENO) == -1)
		exit(1);
	if (close(c.pipe_heredoc0) == -1)
		exit(1);
}
void	e_cmd_cmd(t_data_p *data, t_commands c)
{
	if (c.prev_pfd0)
		if (dup2(c.prev_pfd0, STDIN_FILENO) == -1)
			exit(3);
	if (c.next_pfd1)
		if (dup2(c.next_pfd1, STDOUT_FILENO) == -1)
				exit(4);
	close_all_pipe(data->commands);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(7);
}

void	e_cmd_outfile(t_data_p *data, t_commands c)
{
	if (dup2(c.prev_pfd0, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(c.outfile, STDOUT_FILENO) == -1)
		exit(1);\
	close_all_pipe(data->commands);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
}

void	e_infile_heredoc_cmd(t_data_p *data, t_commands c)
{
	if (c.infile_type == HEREDOC)
	{
		if (close(c.pipe_heredoc1) == -1)
			exit(1);
		if (dup2(c.pipe_heredoc0, STDIN_FILENO) == -1)
			exit(1);
	}
	if (c.infile_type == INFILE)
	{
		if (dup2(c.infile, STDIN_FILENO) == -1)
			exit(1);
	}
	if (c.next_pfd1)
		if (dup2(c.next_pfd1, STDOUT_FILENO) == -1)
			exit(1);
	close_all_pipe(data->commands);
	if (c.infile)
		if (close(c.infile) == -1)
			exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(3);
}

void	e_infile_heredoc_cmd_outfile(t_data_p *data, t_commands c)
{
	if (c.infile_type == HEREDOC)
	{
		if (close(c.pipe_heredoc1) == -1)
			exit(1);
		if (dup2(c.pipe_heredoc0, STDIN_FILENO) == -1)
			exit(1);
	}
	if (c.infile_type == INFILE)
		if (dup2(c.infile, STDIN_FILENO) == -1)
			exit(1);
	if (dup2(c.outfile, STDOUT_FILENO) == -1)
		exit(1);
	close_all_pipe(data->commands);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
}

void	e_exec(t_data_p *data, t_commands *c)
{
	int	i;

	i = -1;
	open_all_pipe(data, c);
	while (!(c[++i].stop))
	{
		if (c[i].infile_type == HEREDOC)
		{
			e_heredoc_pipe(data, &c[i], i);
			c[i].pid_heredoc = fork();
			if (!c[i].pid_heredoc)
			{
				e_heredoc(data, c[i]);
				close_all_pipe(c);
			}
			waitpid(c[i].pid_heredoc, NULL, 0);
			
		}
		c[i].pid = fork();
		if (!c[i].pid)
		{
			if (c[i].infile_type)
			{
				if (c[i].outfile)
					e_infile_heredoc_cmd_outfile(data, c[i]);
				else
					e_infile_heredoc_cmd(data, c[i]);
			}
			else if (c[i].outfile)
				e_cmd_outfile(data, c[i]);
			else
				e_cmd_cmd(data, c[i]);
		}
	}
	close_all_file(c);
	close_all_pipe(c);
	i = -1;
	while (!c[++i].stop)
	{
		if (c[i].pid)
			waitpid(c[i].pid, NULL, 0);
		if (c[i].pid_heredoc)
			waitpid(c[i].pid_heredoc, NULL, 0);
	}
}
