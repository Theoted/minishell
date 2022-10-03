/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_expend_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:37:39 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/03 17:13:16 by theodeville      ###   ########.fr       */
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

// Return 1 si la var n'exist pas; 2 si c'est un $ seul; 0 si la var existe
int	check_expended_var(char *expended_var)
{
	if (ft_strlen(expended_var) == 1)
		return (2);
	if (expended_var[0] == '$')
		return (1);
	return (0);
}

// Fonction qui expend la variable et crée le nouveau buffer.
// C'est cette fonction qui set aussi 
// l'id afin de pouvoir avancer dans le buffer
void	expend_env(char *expended_var, char *buffer,
	t_data_p *data, t_hd_data *hdd)
{
	hdd->tmp = gc_substr(&data->track, buffer, hdd->j, (hdd->i - hdd->j));
	if (expended_var && (!check_expended_var(expended_var)))
	{
		hdd->tmp1 = gc_strjoin(&data->track, hdd->tmp, expended_var);
		hdd->i = set_id_after_env(buffer, hdd->i) - 1;
		hdd->k++;
	}
	else if (expended_var && (check_expended_var(expended_var) == 2))
	{
		hdd->tmp1 = gc_strjoin(&data->track, hdd->tmp, expended_var);
		hdd->k++;
	}
	else
		hdd->tmp1 = gc_strdup(&data->track, hdd->tmp);
	if (expended_var && check_expended_var(expended_var) == 1)
		hdd->i = set_id_after_env(buffer, hdd->i) - 1;
}

// Simple fonction qui fill le new buffer
void	fill_new_buffer(t_data_p *data, t_hd_data *hdd)
{
	if (!hdd->new_buffer)
		hdd->new_buffer = gc_strdup(&data->track, hdd->tmp1);
	else if (hdd->new_buffer)
		hdd->new_buffer = gc_strjoin(&data->track, hdd->new_buffer, hdd->tmp1);
}

// Fonction principale qui permet d'expend ou non les variable d'env.
char	*expend_var_in_buffer(char *buffer,
		char **expended_vars, t_data_p *data)
{
	t_hd_data	hdd;

	init_hdd_struct(&hdd, expended_vars);
	if (!buffer)
		return (NULL);
	while (buffer[++hdd.i])
	{
		hdd.j = hdd.i;
		while (buffer[hdd.i] != '$' && buffer[hdd.i])
			hdd.i++;
		expend_env(expended_vars[hdd.k], buffer, data, &hdd);
		fill_new_buffer(data, &hdd);
	}
	return (hdd.new_buffer);
}
