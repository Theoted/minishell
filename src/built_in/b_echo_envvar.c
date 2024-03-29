/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:27:36 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 17:15:53 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

// Return 1 si il y a un $ sinon return 0
int	check_if_env(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '$')
			return (1);
	return (0);
}

// Revoie l'id du prochain dollard si il y en a un sinon va jusqu'a la fin
// de la string
int	get_next_dollard_id(char *arg, int i)
{
	while (arg[i])
	{
		if (arg[i] == '$' && (state_checker(arg, 0, i) != 39))
			return (i);
		i++;
	}
	return (i);
}

int	get_echo_env_var_doll(t_data *data, char *arg, t_echo_env *e_d, int *i)
{
	int	j;

	j = 1;
	if (check_dol_int(arg, i))
		e_d->tmp = gc_strdup(&data->track, gc_itoa(&data->track, g_status));
	else if (check_num(arg, *i))
		e_d->tmp = gc_strdup(&data->track, "") + (j++ *0);
	else
	{		
		while ((ft_isalnum(arg[(*i) + j]) || arg[(*i) + j] == '_')
			&& arg[(*i) + j])
			j++;
		if (j == 1)
			e_d->tmp = gc_strdup(&data->track, "$");
		else if (arg[(*i)] && state_checker(arg, 0, *i) == 39)
			e_d->tmp = gc_substr(&data->track, arg, (*i), j);
		else
		{
			e_d->tmp = gc_substr(&data->track, arg, (*i), j);
			expend_echo_env_vars(data, &e_d->tmp);
		}
	}
	echo_env_var_doll2(data, e_d, i, j);
	return (0);
}

// Recupere une argument dans lequel il y aurais une variable d'environnement
// ou plus et expend ou non les variables presente puis renvoie l'argument
char	*get_echo_env_var(t_data *data, char *arg)
{
	int			i;
	t_echo_env	e_d;

	i = -1;
	e_d.new = "";
	while (arg[++i])
	{
		if (arg[i] != '$')
		{
			if (!e_d.new)
				e_d.new = gc_substr(&data->track, arg, i,
						get_next_dollard_id(arg, i));
			else
			{
				e_d.new = gc_strjoin(&data->track, e_d.new,
						gc_substr(&data->track, arg, i,
							get_next_dollard_id(arg, i) - i));
			}
			i = get_next_dollard_id(arg, i) - 1;
		}
		else if (arg[i] == '$')
			get_echo_env_var_doll(data, arg, &e_d, &i);
	}
	return (e_d.new);
}

int	expend_echo_env_vars(t_data *data, char **arg)
{
	char	*tmp;

	tmp = *arg;
	if (*arg[0] == '$')
	{
		*arg = expend_env_var(data->envp, *(arg) + 1);
		if (!strncmp_len(gc_strjoin(&data->track, "$", *arg), tmp))
			*arg = gc_strdup(&data->track, "");
	}
	return (0);
}
