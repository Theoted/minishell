/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:27:36 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/29 14:02:58 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	check_num(char *arg, int i)
{
	if (arg[i + 1] >= 48 && arg[i + 1] <= 57 && state_checker(arg, 0, i) != 39)
		return (1);
	return (0);
}

int	get_echo_env_var_doll(t_data_p *data, char *arg, t_echo_env *e_d, int *i)
{
	int	j;

	j = 1;
	if (check_num(arg, *i))
	{
		e_d->tmp = gc_strdup(&data->track, "");
		j++;
	}
	else
	{		
		while ((ft_isalnum(arg[(*i) + j]) || arg[(*i) + j] == '_')
			&& arg[(*i) + j])
			j++;
		if (j == 1)
			e_d->tmp = gc_strdup(&data->track, "$");
		else if (arg[(*i) - 1] && state_checker(arg, 0, *i) == 39)
			e_d->tmp = gc_substr(&data->track, arg, (*i), j);
		else
		{
			e_d->tmp = gc_substr(&data->track, arg, (*i), j);
			expend_echo_env_vars(data, &e_d->tmp);
		}
	}
	if (!e_d->new)
		e_d->new = gc_strdup(&data->track, e_d->tmp);
	else
		e_d->new = gc_strjoin(&data->track, e_d->new, e_d->tmp);
	(*i) += j - 1;
	return (0);
}

// Recupere une argument dans lequel il y aurais une variable d'environnement
// ou plus et expend ou non les variables presente puis renvoie l'argument
char	*get_echo_env_var(t_data_p *data, char *arg)
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

int	expend_echo_env_vars(t_data_p *data, char **arg)
{
	char	*tmp;

	tmp = *arg;
	if (*arg[0] == '$')
	{
		*arg = expend_env_var(data, data->envp, *(arg) + 1);
		if (!strncmp_len(gc_strjoin(&data->track, "$", *arg), tmp))
			*arg = gc_strdup(&data->track, "");
	}
	return (0);
}
