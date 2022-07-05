/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_clear_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:10:40 by tdeville          #+#    #+#             */
/*   Updated: 2022/06/28 11:38:35 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *clear_here_doc(t_data_p *data, char *arg)
{
	int		i;
	int		j;
	char	*new;
	char	*tmp;

	i = -1;
	new = 0;
	tmp = 0;
	while (arg[++i])
	{
		j = i;
		while (arg[i] != '<' && arg[i])
			i++;
		if (arg[i] == '<' && arg[i + 1] == '<')
		{
			tmp = gc_substr(&data->track, arg, j, i);
			i += 2;
			while (arg[i] == ' ' && arg[i])
				i++;
			while (arg[i] != ' ' && arg[i])
				i++;
		}
		if (!new && tmp)
		{
			new = gc_strdup(&data->track, tmp);
			tmp = 0;
		}
		else if (new && tmp)
		{
			new = gc_strjoin(&data->track, new, tmp);
			tmp = 0;
		}
	}
	printf("new = %s\n", new);
	return (0);
}
