/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:28:03 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/07 01:10:57 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nb_of_env_vars(char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$')
			count++;
		i++;
	}
	return (count);
}

// Revoie 1 si la variable est seule dans
// le buffer et que son premier char est $ 
// sinon renvoie 0
// Renvoi 2 si le premier char est un dollard,
// et que le deuxieme est un char non alphanum
int	check_solo_var(char *buffer)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (buffer[i] == '$')
	{
		while (buffer[++i])
		{
			if (buffer[i] == '$')
				check++;
		}
		i = -1;
		while (buffer[++i])
		{
			if (!ft_isalnum(buffer[i]))
			{
				if (check_var(buffer))
					return (2);
				return (0);
			}
		}
		return (1);
	}
	return (0);
}

// Check si le premier char est un $ si oui
// Renvoi 1 si il y a un char non alphanum apres le dollard sinon renvoie 0
int	check_var(char *var)
{
	if (var[0] == '$')
	{
		if (!ft_isalnum(var[1]))
			return (1);
		return (0);
	}
	return (1);
}

char	*check_bsn_buffer(t_data *data, char *new_buffer)
{
	int		len;

	len = ft_strlen(new_buffer);
	if (new_buffer[len - 1] != '\n')
	{
		new_buffer = gc_strjoin(&data->track, new_buffer, "\n");
		return (new_buffer);
	}
	return (new_buffer);
}

char	*trim_last_bsn(t_data *data, char *here_doc_content)
{
	int		len;

	len = ft_strlen(here_doc_content);
	if (here_doc_content[len - 1] == '\n')
	{
		here_doc_content
			= gc_substr(&data->track, here_doc_content, 0, len - 1);
		return (here_doc_content);
	}
	return (here_doc_content);
}
