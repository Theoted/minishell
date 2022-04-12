/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/04/12 13:43:28 by pat              ###   ########lyon.fr   */
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
	if (c.prev_pfd1)
		if (close(c.prev_pfd1) == -1)
			exit(1);
	if (c.next_pfd0)
	{
		dprintf(2, "000000000\n");
		if (close(c.next_pfd0) == -1)
			exit(2);
	}
	if (c.prev_pfd0)
	{
		if (dup2(c.prev_pfd0, STDIN_FILENO) == -1)
			exit(3);
	}
	if (c.next_pfd1)
	{
		dprintf(2, "111111111\n");
		if (dup2(c.next_pfd1, STDOUT_FILENO) == -1)
				exit(4);
	}
	if (c.prev_pfd0)
	{
		if (close(c.prev_pfd0) == -1)
			exit(5);
	}
	if (c.next_pfd1)
	{
			dprintf(2, "2222222222\n");
		if (close(c.next_pfd1) == -1)
			exit(6);
	}
	dprintf(2, "##########\n");
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(7);
}

void	e_cmd_outfile(t_data_p *data, t_commands c)
{
	if (close(c.prev_pfd1) == -1)
		exit(1);
	if (dup2(c.prev_pfd0, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(c.outfile, STDOUT_FILENO) == -1)
		exit(1);
	if (close(c.prev_pfd0) == -1)
		exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
	if (close(c.outfile) == -1)
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
	if (c.next_pfd0)
	{
		if (close(c.next_pfd0) == -1)
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
	if(c.next_pfd1)
		if (close(c.next_pfd1) == -1)
			exit(1);
	if (c.infile)
		if (close(c.infile) == -1)
			exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(3);
}

void	e_infile_heredoc_cmd_outfile(t_data_p *data, t_commands c)
{
	dprintf(2, "222222222\n");
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
	if (dup2(c.outfile, STDOUT_FILENO) == -1)
		exit(1);
	if (close(c.outfile) == -1)
		exit(1);
	if (execve (c.cmd_path, c.args_vec, c.envp) == -1)
		exit(1);
	if(c.infile_type == 2)
		if (close(c.infile) == -1)
			exit(1);
	if (close(c.outfile) == -1)
		exit(1);
}

void	e_exec(t_data_p *data, t_commands *c)
{
	int	i;

	i = -1;
	open_all_pipe(data, c);
	int fd = open("error.txt", O_WRONLY);
	printf("fd == %i\n", fd);
	printf("next_pfd1 = %i\n", data->commands[0].next_pfd1);
	printf("next_pfd0 = %i\n", data->commands[0].next_pfd0);
	printf("prev_pfd1 = %i\n", data->commands[0].prev_pfd1);
	printf("prev_pfd0 = %i\n", data->commands[0].prev_pfd0);
	printf("data argv0 = %s\n", data->commands[0].args_vec[0]);
	printf("data argv1 = %s\n", data->commands[0].args_vec[1]);
	printf("data cmd_path = %s\n", data->commands[0].cmd_path);
	printf("fd_infile = %i\n", data->commands[0].infile);
	printf("fd_outfile = %i\n", data->commands[0].outfile);
	printf("fd heredoc1 = %i\n", data->commands[0].pipe_heredoc1);
	printf("fd heredoc0 = %i\n", data->commands[0].pipe_heredoc0);
	close (fd);
	
	printf("++++++++++++++++++++++++++++\n");
	printf("next_pfd1 = %i\n", data->commands[1].next_pfd1);
	printf("next_pfd0 = %i\n", data->commands[1].next_pfd0);
	printf("prev_pfd1 = %i\n", data->commands[1].prev_pfd1);
	printf("prev_pfd0 = %i\n", data->commands[1].prev_pfd0);
	printf("data argv = %s\n", data->commands[1].args_vec[0]);
	printf("data argv = %s\n", data->commands[1].args_vec[1]);
	printf("data cmd_path = %s\n", data->commands[1].cmd_path);
	printf("fd_infile = %i\n", data->commands[1].infile);
	printf("fd_outfile = %i\n", data->commands[1].outfile);
	// printf("++++++++++++++++++++++++++++\n");
	// printf("next_pfd1 = %i\n", data->commands[2].next_pfd1);
	// printf("next_pfd0 = %i\n", data->commands[2].next_pfd0);
	// printf("data argv = %s\n", data->commands[2].args_vec[0]);
	// printf("data argv = %s\n", data->commands[2].args_vec[1]);
	// printf("data cmd_path = %s\n", data->commands[2].cmd_path);
	// printf("fd_infile = %i\n", data->commands[2].infile);
	// printf("fd_outfile = %i\n", data->commands[2].outfile);
	// printf("data stop = %i\n", data->commands[2].stop);
	printf("\n\n");
	while (!(c[++i].stop))
	{
		if (c[i].infile_type == HEREDOC)
		{
			e_heredoc_pipe(data, &c[i], i);
			c[i].pid_heredoc = fork();
			if (c[i].pid_heredoc == 0)
				e_heredoc(data, c[i]);
			close_all_pipe(c);
			waitpid(c[i].pid_heredoc, NULL, 0);
			
		}
		c[i].pid = fork();
		// dprintf(2, "pid === %i\n", c[i].pid);
		if (!c[i].pid)
		{
			if (c[i].infile_type)
			{
				if (c[i].outfile)
				{
					e_infile_heredoc_cmd_outfile(data, c[i]);
				}
				else
				{
					e_infile_heredoc_cmd(data, c[i]);
				}
			}
			else if (c[i].outfile)
			{
				e_cmd_outfile(data, c[i]);
			}
			else
			{
				e_cmd_cmd(data, c[i]);
			}
		}
	}
	close_all_pipe(c);
	close_all_file(c);
	i = -1;
	while (!c[++i].stop)
	{
		dprintf(2, "pid == %i\n", c[i].pid);
		if (c[i].pid)
		{
			waitpid(c[i].pid, NULL, 0);
		}
		if (c[i].pid)
		{
			waitpid(c[i].pid_heredoc, NULL, 0);
		}
	}
}
