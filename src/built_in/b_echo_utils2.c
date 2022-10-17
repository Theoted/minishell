/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:18:37 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 16:34:17 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

char	*check_exit_status(t_data *data, char *arg, int i)
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
		if (arg[i] && arg[i] == '$' && arg[i + 1] == '?')
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
		if (!arg[i])
			break ;
	}
	return (tmp1);
}

void	echo_env_var_doll2(t_data *data, t_echo_env *e_d, int *i, int j)
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

// Cette fonction supprimer les quotes a supprimer dans l'argument
void	parse_quotes(t_data *data, t_echo *echo_data, int *i, char *arg)
{
	char	*tmp;

	tmp = NULL;
	if (echo_data->new == NULL)
		echo_data->new
			= gc_substr(&data->track, echo_data->arg, echo_data->idx + 1,
				next_quote_id(echo_data->arg,
					echo_data->quote, echo_data->idx) - 1);
	else
	{
		tmp = echo_data->new;
		echo_data->new
			= gc_substr(&data->track, echo_data->arg, echo_data->idx + 1,
				next_quote_id(echo_data->arg,
					echo_data->quote, echo_data->idx)
				- 1 - echo_data->idx);
		echo_data->new = gc_strjoin(&data->track, tmp, echo_data->new);
	}
	(*i) = next_quote_id(arg, echo_data->quote, (*i));
	echo_data->quote = 0;
}

void	ft_while_remove_quotes(t_data *data, char *arg, t_echo *echo_data)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		echo_data->idx = i;
		if ((arg[i] == '\'' || arg[i] == '\"') && !state_checker(arg, 0, i))
		{
			echo_data->quote = arg[i];
			if (next_quote_id(arg, echo_data->quote, i) != -1)
				parse_quotes(data, echo_data, &i, arg);
		}
		else if ((arg[i] != '\'' || arg[i] != '\"')
			&& !state_checker(arg, 0, i))
		{
			e_create_arg(data, echo_data);
			i = word_end_id(arg, i) - 1;
		}
	}
}
