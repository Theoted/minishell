/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_open_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:25:52 by pat               #+#    #+#             */
/*   Updated: 2022/10/10 14:38:21 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	open_infile(t_tokens *token, char *infile)
{
	token->fd_in = open(infile, O_DIRECTORY);
	if (token->fd_in != 0 && token->fd_in != -1)
	{
		write(2, infile, ft_strlen(infile));
		write(2, " : is a directory\n", 19);
		close(token->fd_in);
		// close (token->pfd[1]);
		// close (token->pfd[0]);
		return (0);
	}
	token->fd_in = open(infile, O_RDONLY);
	if (token->fd_in == -1)
	{
		perror(infile);
		return (0);
	}
	return (1);
}

int	open_outfile(t_tokens *token, char *outfile)
{
	token->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (token->fd_out == -1)
	{
		// close (token->pfd[1]);
		// close (token->pfd[0]);
		perror(outfile);
		return (0);
	}
	return (1);
}

/* Ouverture de l'outfile_hb */
int	open_outfile_hb(t_tokens *token, char *outfile_hb)
{
	token->fd_out = open(outfile_hb, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (token->fd_out == -1)
	{
		// close (token->pfd[1]);
		// close (token->pfd[0]);
		perror(outfile_hb);
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
