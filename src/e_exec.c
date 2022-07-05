/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/07/05 17:01:16 by pat              ###   ########lyon.fr   */
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
	close(c->pfd[0]);
	open_files (c);
	if (!c->fd_in)
		return (0);
	if (!c->fd_out)
		return (0);
	if (c->last_in_type == HEREDOC_TYPE)
		e_heredoc(c);
	if (c->last_in_type != HEREDOC_TYPE)
		dup2(c->fd_in, STDIN_FILENO);
	if (c->fd_in)
		close(c->fd_in);
	else
		dup2(c->pfd[1], STDOUT_FILENO);
	close(c->pfd[1]);
	check_path(d, c);
	e_execve(c);
	exit(1);
}

/* Parcours le tableau de commande et fork apres chaque commandes pour l'executer et creation du pipe */
void	e_exec(t_data_p *d, t_commands *c)
{
	int	i;

	c->fd_in = 0;
	i = -1;
	while (c[++i].stop == 0)
	{
		pipe(c[i].pfd);
		c[i].pid = fork();
		if (!c[i].pid)
		{
			// dprintf(2, "/////%i/////\n", i);
			// dprintf(2, "infile = %s\n", c[i].files[0].file);
			// dprintf(2, "infile_type = %i\n", c[i].files[0].type);
			// dprintf(2, "last_infile_type = %i\n", c[i].last_in_type);
			// dprintf(2, "outfile = %s\n", c[i].files[1].file);
			// dprintf(2, "outfile_type = %i\n", c[i].files[1].type);
			// dprintf(2, "envp = %s\n", c[i].envp[1]);
			// dprintf(2, "cmd_path = %s\n", c[i].cmd_path);
			// dprintf(2, "cmd = %s\n", c[i].args_vec[0]);
			// dprintf(2, "/////FIN/////\n");
			if (!e_child(d, &c[i]))
				return ;
		}
		else
		{
			close(c[i].pfd[1]);
			if (c[i].fd_in)
				close(c->fd_in);
			if (c[i].fd_out)
				close(c[i].fd_out);
			c[i].fd_in = dup(c->pfd[0]);
			close(c[i].pfd[0]);
		}
	}
	i = -1;
	while (c[++i].stop == 0)
		waitpid(c[i].pid, NULL, 0);
}