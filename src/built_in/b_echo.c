/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:56:07 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/11 08:34:02 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_ed(t_echo_2 *echo_data, t_data *data, int idx)
{
	echo_data->bn = 1;
	echo_data->new = NULL;
	echo_data->av_len = arg_vec_len(data, idx);
	echo_data->check = 0;
}

// Cette fonction recuperer les mots qui ne sont pas entre quotes
void	e_create_arg(t_data *data, t_echo *echo_data)
{
	char	*tmp;

	tmp = NULL;
	if (echo_data->new == NULL)
	{
		echo_data->new
			= gc_substr(&data->track, echo_data->arg, echo_data->idx,
				word_end_id(echo_data->arg, echo_data->idx));
	}
	else
	{
		tmp = echo_data->new;
		echo_data->new
			= gc_substr(&data->track, echo_data->arg, echo_data->idx,
				word_end_id(echo_data->arg, echo_data->idx) - echo_data->idx);
		echo_data->new = gc_strjoin(&data->track, tmp, echo_data->new);
	}
}

// Cette fonction est la fonction PRINCIPALE qui permet de parser un
// argument en lui enlevant les quotes necessaires
char	*remove_quotes(t_data *data, char *arg)
{
	t_echo	echo_data;

	remove_quote_init(&echo_data, arg);
	if (!arg)
		return ("");
	ft_while_remove_quotes(data, arg, &echo_data);
	return (echo_data.new);
}

void	b_echo(t_data *data, int idx)
{
	int			i;
	t_echo_2	e_d;

	init_ed(&e_d, data, idx);
	i = 0;
	while (++i < e_d.av_len + 1)
	{
		if (check_n(data->commands[idx].args_vec[i], -1) && e_d.check == 0)
		{
			e_d.bn = 0;
			continue ;
		}
		e_d.check = 1;
		data->commands[idx].args_vec[i] = check_exit_status
			(data, data->commands[idx].args_vec[i], -1);
		printf("%s", remove_quotes(data, data->commands[idx].args_vec[i]));
		if (e_d.av_len > 1
			&& i < e_d.av_len
			&& data->commands[idx].args_vec[i])
			printf(" ");
	}
	if (e_d.bn)
		printf("\n");
	exit(0);
}
