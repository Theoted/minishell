/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expend_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:42:56 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/22 10:09:56 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// je dois faire une fonction qui expend (ou pas) les variables d'env dans mon argument
// voir si je peux pas faire une fonction qui a la fois expend les vars et a la fois
// enleve les quotes

char	**get_exp_vars_arg(char *arg, t_data_p *data)
{
	int		i;
	int		k;
	char	**vars;
	char	*tmp;

	i = -1;
	k = 0;
	vars = gc_calloc(sizeof(char *), (nb_of_env_vars(arg) + 1), &data->track);
	while (arg[++i])
		if (arg[i] == '$')
			fill_vars_tab(data, &vars[k], arg, &i, &k);
	vars[k] = 0;
	i = 0;
	if (vars)
	{
		while (vars[i])
		{
			tmp = vars[i];
			vars[i] = expend_env_var(data, data->env_vars, vars[i]);
			if (!ft_strncmp(vars[i], tmp, ft_strlen(vars[i])))
				vars[i] = gc_strjoin(&data->track, "$", tmp);
			i++;
		}
	}
	return (vars);
}

// int	check_arg_vars(char *arg, t_data_p *data)
// {
// 	char	**args;
// 	char	*new_arg;
// 	int		i;
// 	int		j;
// 	int		k;

// 	args = get_exp_vars_arg(arg, data);
// 	while (arg[i])
// 	{
		
// 	}
// 	return (0);
// }
