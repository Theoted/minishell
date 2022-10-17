/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_open_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/10/17 14:52:13 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	open_infile(t_tokens *token, char *infile)
{
	if(token->fd_in)
		close(token->fd_in);
	token->fd_in = open(infile, O_DIRECTORY);
	if (token->fd_in != 0 && token->fd_in != -1)
	{
		write(2, infile, ft_strlen(infile));
		write(2, " : is a directory\n", 19);
		g_status = 1;
		close(token->fd_in);
		return (0);
	}
	if (token->fd_in != 0 && token->fd_in != -1)
		close(token->fd_in);
	token->fd_in = open(infile, O_RDONLY);
	if (token->fd_in == -1)
	{
		perror(infile);
		g_status = 1;
		return (0);
	}
	return (1);
}

int	open_outfile(t_tokens *token, char *outfile)
{
	if (token->fd_out && token->fd_out != 1)
		close(token->fd_out);
	token->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (token->fd_out == -1)
	{
		perror(outfile);
		g_status = 1;
		return (0);
	}
	return (1);
}

/* Ouverture de l'outfile_hb */
int	open_outfile_hb(t_tokens *token, char *outfile_hb)
{
	if (token->fd_out && token->fd_out != 1)
		close(token->fd_out);
	token->fd_out = open(outfile_hb, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (token->fd_out == -1)
	{
		close (token->pfd[1]);
		close (token->pfd[0]);
		perror(outfile_hb);
		g_status = 1;
		return (0);
	}
	return (1);
}

/* Ouverture de tous les files dans l'ordre */

int	open_files(t_tokens *token)
{
	int	i;

	i = -1;
	while (!token->files[++i].stop)
	{
		if (token->files[i].type == INFILE)
		{
			if (open_infile(token, token->files[i].file_name) == 0)
				return (0);
		}
		else if (token->files[i].type == OUTFILE)
		{
			if (open_outfile(token, token->files[i].file_name) == 0)
				return (0);
		}
		else if (token->files[i].type == OUTFILE_HB)
		{
			if (open_outfile_hb(token, token->files[i].file_name) == 0)
				return (0);
		}
	}
	return (1);
}
