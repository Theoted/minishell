/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/07/22 20:22:48 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Ouverture de l'infile */
int	open_infile(t_commands *c, char *infile)
{
	c->fd_in = open(infile, O_DIRECTORY);
	if (c->fd_in != 0 && c->fd_in != -1)
	{
		write(2, c->files[1].file, ft_strlen(infile));
		write(2, " : is a directory\n", 19);
	}
	close(c->fd_in);
	c->fd_in = open(infile, O_RDONLY);
	if (c->fd_in == -1)
	{
		perror(infile);
		return (0);
	}
	return (1);
}
/* Ouverture de l'outfile */
int	open_outfile(t_commands *c, char *outfile)
{
	c->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0660);
	if (c->fd_out == -1)
	{
		perror(outfile);
		return (0);
	}
	dup2(c->fd_out, STDOUT_FILENO);
	close(c->fd_out);
	return (1);
}
/* Ouverture de l'outfile_hb */
int	open_outfile_hb(t_commands *c, char *outfile_hb)
{
	c->fd_out = open(outfile_hb, O_WRONLY | O_CREAT | O_APPEND, 0660);
	if (c->fd_out == -1)
	{
		perror(outfile_hb);
		return (0);
	}
	dup2(c->fd_out, STDOUT_FILENO);
	close(c->fd_out);
	return (1);
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

/* Ouverture de tous les files dans l'ordre */
int	open_files(t_commands *c)
{
	int	i;

	i = -1;
	while (!c->files[++i].stop)
	{
		if (c->files[i].type == INFILE)
		{
			if(open_infile(c, c->files[i].file) == 0)
				return (0);
		}
		else if (c->files[i].type == OUTFILE)
		{
			if(open_outfile(c, c->files[i].file) == 0)
				return (0);
		}
		else if (c->files[i].type == OUTFILE_HB)
		{
			if (open_outfile_hb(c, c->files[i].file) == 0)
				return (0);
		}
	}
	return (1);
}

/* execution de la commande dans le child */
int	e_child(t_data_p *d,t_commands *c)
{
	open_files (c);
	if (c->last_in_type == HEREDOC_TYPE)
		e_heredoc(c);
	if (c->last_in_type != HEREDOC_TYPE)
		dup2(c->fd_in, STDIN_FILENO);
	if (c->fd_in)
		close(c->fd_in);
	close(c->pfd[0]);
	if(c->fd_out == 0)
		dup2(c->pfd[1], STDOUT_FILENO);
	close(c->pfd[1]);
	check_path(d, c);
	e_execve(c);
	return (1);
}

/* Parcours le tableau de commande et fork apres chaque commandes pour l'executer et creation du pipe */
void	e_exec(t_data_p *d, t_commands *c)
{
	int	i;

	i = -1;
	while (c[++i].stop == 0)
	{
		if (c[i + 1].stop)
			c[i].fd_out = 1;
		pipe(c[i].pfd);
		c[i].pid = fork();
		if (!c[i].pid)
		{
			if (!e_child(d, &c[i]))
				return ;
		}
		else
		{
			close(c[i].pfd[1]);
			if (c[i].fd_in)
				close(c[i].fd_in);
			c[i + 1].fd_in = dup(c->pfd[0]);
			close(c[i].pfd[0]);
		}
	}
	i = -1;
	while (c[++i].stop == 0)
		waitpid(c[i].pid, NULL, 0);
}