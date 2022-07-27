/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_expend_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:37:39 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/27 16:04:57 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_hdd_struct(t_hd_data *hdd, char **expended_vars)
{
	hdd->i = -1;
	hdd->k = 0;
	hdd->new_buffer = 0;
	hdd->tmp = 0;
	hdd->tmp1 = 0;
	hdd->check = 0;
	hdd->expended_vars = expended_vars;
}

void	expend_var_in_buffer1(char *buffer, char **expended_vars, t_hd_data *hdd, t_data_p *data)
{
	hdd->tmp = gc_substr(&data->track, buffer, hdd->j, (hdd->i - hdd->j));
	if (expended_vars[hdd->k] && check_var(expended_vars[hdd->k]))
		hdd->tmp1 = gc_strjoin(&data->track,
				hdd->tmp, expended_vars[hdd->k++]);
	else if (expended_vars[hdd->k] && !check_var(expended_vars[hdd->k]))
	{
		hdd->tmp1 = gc_strdup(&data->track, hdd->tmp);
		hdd->check = 1;
				hdd->k++;
	}
	else if (!expended_vars[hdd->k])
		hdd->tmp1 = gc_strdup(&data->track, hdd->tmp);
}

void	expend_var_in_buffer2(char *buffer, char **expended_vars, t_hd_data *hdd, t_data_p *data)
{
	if (check_solo_var(buffer) == 1 && expended_vars[hdd->k][0] == '$')
		hdd->tmp1 = gc_strdup(&data->track, "");
	else if (check_solo_var(buffer) == 2)
	{
		hdd->tmp1 = gc_strdup(&data->track, buffer);
		hdd->check = 2;
	}
	else if (expended_vars[hdd->k] && check_var(expended_vars[hdd->k]))
		hdd->tmp1
			= gc_strdup(&data->track, expended_vars[hdd->k++]);
	else if (expended_vars[hdd->k] && !check_var(expended_vars[hdd->k]))
	{
		hdd->check = 1;
		hdd->k++;
	}
}

void	expend_var_in_buffer3(char *buffer, char **expended_vars, t_hd_data *hdd, t_data_p *data)
{
		while (buffer[hdd->i])
		{
			if (hdd->check == 1 && (buffer[hdd->i + 1] == '\''
					|| buffer[hdd->i + 1] == '\"') && hdd->check != 2)
			{
				hdd->check = 0;
				break ;
			}
			if (!ft_isalnum(buffer[hdd->i + 1])
				&& hdd->check != 2)
				break ;
			hdd->i++;
		}
}

// Cette fonction est la fonction qui expend toutes les variables
// d'environnement dans le buffer
char	*expend_var_in_buffer(char *buffer,
		char **expended_vars, t_data_p *data)
{
	t_hd_data	hdd;

	init_hdd_struct(&hdd, expended_vars);
	while (buffer[++hdd.i])
	{
		hdd.j = hdd.i;
		while (buffer[hdd.i] != '$' && buffer[hdd.i])
			hdd.i++;
		if (hdd.i > 0)
			expend_var_in_buffer1(buffer, expended_vars, &hdd, data);
		else if (hdd.i == 0)
			expend_var_in_buffer2(buffer, expended_vars, &hdd, data);
		expend_var_in_buffer2(buffer, expended_vars, &hdd, data);
		if (!hdd.new_buffer && hdd.tmp1)
			hdd.new_buffer
				= gc_strdup(&data->track, hdd.tmp1);
		else if (!hdd.new_buffer && !hdd.tmp1)
			continue ;
		else
			hdd.new_buffer = gc_strjoin(&data->track,
					hdd.new_buffer, hdd.tmp1);
	}
	hdd.new_buffer = check_bsn_buffer(data, hdd.new_buffer);
	return (hdd.new_buffer);
}
