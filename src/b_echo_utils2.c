/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:18:37 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/04 13:17:06 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	*check_exit_status(t_data_p *data, char *arg, int i)
{
	int		j;
	char	*tmp;
	char	*tmp1;

	tmp = NULL;
	tmp1 = NULL;
	while (arg[++i])
	{
		j = i;
		while (arg[i] && arg[i] != '$')
			i++;
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			tmp = gc_strjoin(&data->track, gc_substr
					(&data->track, arg, j, (i - j)), ft_itoa(g_status));
			i++;
		}
		else
			tmp = gc_substr(&data->track, arg, j, (i + 1 - j));
		if (!tmp1)
			tmp1 = gc_strdup(&data->track, tmp);
		else
			tmp1 = gc_strjoin(&data->track, tmp1, tmp);
	}
	return (tmp1);
}

void	echo_env_var_doll2(t_data_p *data, t_echo_env *e_d, int *i, int j)
{
	if (!e_d->new)
		e_d->new = gc_strdup(&data->track, e_d->tmp);
	else
		e_d->new = gc_strjoin(&data->track, e_d->new, e_d->tmp);
	(*i) += j - 1;
}

int	check_num(char *arg, int i)
{
	if (arg[i + 1] >= 48 && arg[i + 1] <= 57 && state_checker(arg, 0, i) != 39)
		return (1);
	return (0);
}
