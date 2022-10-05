/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_open_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/10/05 19:57:30 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	open_infile(t_commands *c, char *infile)
{
	c->fd_in = open(infile, O_DIRECTORY);
	if (c->fd_in != 0 && c->fd_in != -1)
	{
		write(2, infile, ft_strlen(infile));
		write(2, " : is a directory\n", 19);
		return (0);
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
	c->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (c->fd_out == -1)
	{
		perror(outfile);
		return (0);
	}
	return (1);
}

/* Ouverture de l'outfile_hb */
int	open_outfile_hb(t_commands *c, char *outfile_hb)
{
	c->fd_out = open(outfile_hb, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (c->fd_out == -1)
	{
		perror(outfile_hb);
		return (0);
	}
	return (1);
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
			if (open_infile(c, c->files[i].file_name) == 0)
				return (0);
		}
		else if (c->files[i].type == OUTFILE)
		{
			if (open_outfile(c, c->files[i].file_name) == 0)
				return (0);
		}
		else if (c->files[i].type == OUTFILE_HB)
		{
			if (open_outfile_hb(c, c->files[i].file_name) == 0)
				return (0);
		}
	}
	return (1);
}
