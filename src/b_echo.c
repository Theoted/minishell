/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:56:07 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/15 10:33:44 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_ed(t_echo_2 *echo_data, t_data_p *data, int idx)
{
	echo_data->bn = 1;
	echo_data->new = NULL;
	echo_data->av_len = arg_vec_len(data, idx);
	echo_data->check = 0;
}

// Cette fonction supprimer les quotes a supprimer dans l'argument
void	parse_quotes(t_data_p *data, t_echo *echo_data, int *i, char *arg)
{
	char	*tmp;

	tmp = NULL;
	if (echo_data->new == NULL)
		echo_data->new
			= gc_substr(&data->track, echo_data->arg, echo_data->idx + 1,
				next_quote_id(echo_data->arg,
					echo_data->quote, echo_data->idx, echo_data) - 1);
	else
	{
		tmp = echo_data->new;
		echo_data->new
			= gc_substr(&data->track, echo_data->arg, echo_data->idx + 1,
				next_quote_id(echo_data->arg,
					echo_data->quote, echo_data->idx, echo_data)
				- 1 - echo_data->idx);
		echo_data->new = gc_strjoin(&data->track, tmp, echo_data->new);
	}
	(*i) = next_quote_id(arg, echo_data->quote, (*i), echo_data);
	echo_data->quote = 0;
}

// Cette fonction recuperer les mots qui ne sont pas entre quotes
void	e_create_arg(t_data_p *data, t_echo *echo_data)
{
	char	*tmp;

	tmp = NULL;
	if (echo_data->new == NULL)
		echo_data->new
			= gc_substr(&data->track, echo_data->arg, echo_data->idx,
				word_end_id(echo_data->arg, echo_data->idx));
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
char	*remove_quotes(t_data_p *data, char *arg)
{
	t_echo	echo_data;
	int		i;

	i = -1;
	echo_data.new = NULL;
	echo_data.quote = 0;
	echo_data.arg = arg;
	if (!arg)
		return ("");
	while (arg[++i])
	{
		echo_data.idx = i;
		if ((arg[i] == '\'' || arg[i] == '\"') && !state_checker(arg, 0, i))
		{
			echo_data.quote = arg[i];
			if (next_quote_id(arg, echo_data.quote, i, &echo_data) != -1)
				parse_quotes(data, &echo_data, &i, arg);
		}
		else if ((arg[i] != '\'' || arg[i] != '\"')
			&& !state_checker(arg, 0, i))
		{
			e_create_arg(data, &echo_data);
			i = word_end_id(arg, i) - 1;
		}
	}
	return (echo_data.new);
}

void	b_echo(t_data_p *data, int idx)
{
	int			i;
	t_echo_2	e_d;

	init_ed(&e_d, data, idx);
	i = 0;
	while (data->commands[idx].args_vec[++i])
	{
		if (check_n(data->commands[idx].args_vec[i]) && e_d.check == 0)
		{
			e_d.bn = 0;
			continue ;
		}
		e_d.check = 1;
		data->commands[idx].args_vec[i] = get_echo_env_var
			(data, data->commands[idx].args_vec[i]);
		data->commands[idx].args_vec[i] = echo_parse_bs
			(data->commands[idx].args_vec[i], data);
		printf("%s", remove_quotes(data, data->commands[idx].args_vec[i]));
		if (e_d.av_len > 1 && i < e_d.av_len)
			printf(" ");
	}
	if (e_d.bn)
		printf("\n");
	exit(0);
}
