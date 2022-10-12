/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:29:36 by theodeville       #+#    #+#             */
/*   Updated: 2022/10/12 20:49:26 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	contains_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int check_name(char *arg)
{
	int	i;

	i = 0;
	if (contains_equal(arg))
	{
		if (arg[i] == '_' || ft_isalpha(arg[i]))
		{
			i++;
			while (arg[++i])
			{
				if (!ft_isalnum((int)arg[i]) || arg[i] != '_')
				{
					return (0);
				}
				if (arg[i] == '=')
					return (1);
			}
		}
		return (0);
	}
	return (1);
}


// Creer une variable d'environnement avec un contenu qui pointe sur NULL
int	create_var_no_content(t_data *data, char *arg,
	t_export *expstr)
{
	expstr->name = gc_strdup(&data->track, arg);
	expstr->content = NULL;
	return (1);
}

int	check_arg(t_data *data, char *arg, t_export *expstr)
{
	int		i;
	t_envp	*tmp;

	i = -1;
	tmp = data->envp;
	data->exp_equal = 0;
	if (arg[0] == '=')
	{
		g_status = 1;
		return (export_error_arg(arg));
	}
	if (!contains_equal(arg))
	{
		if (!check_if_exist(tmp, arg))
			return (create_var_no_content
				(data, arg, expstr));
		return (1);
	}
	else if (contains_equal(arg) == -1)
		return (-1);
	while (arg[++i] && arg[i] != '=')
		if (arg[i] == ' ')
			return (1);
	expstr->name = gc_substr(&data->track, arg, 0, i);
	expstr->content = remove_quotes(data, gc_substr
			(&data->track, arg, i + 1, ft_strlen(arg) - i));
	expstr->equal = 1;
	return (0);
}

// void	init_export_vars(t_export *exp_str, t_envp **in_list)
void	init_export_vars(t_export *exp_str)
{
	exp_str->content = NULL;
	exp_str->name = NULL;
	exp_str->equal = 0;
}

int	b_export(t_data *data, int idx)
{
	int			i;
	t_envp		*in_list;
	t_export	exp_str;

	i = 1;
	// int j = -1;

	if (!arg_vec_len(data, idx))
		print_export(data, data->envp, idx);
	while (data->commands[idx].args_vec[i])
	{
		printf("idx = %d\n", idx);
		init_export_vars(&exp_str);
		if (i == 1)
		{
			if (!check_name(data->commands[idx].args_vec[i]))
			{
				
				write(2, data->commands[idx].args_vec[1], strlen(data->commands[idx].args_vec[1]));
				write(2, ": not a valid identifier\n", 26);
				g_status = 1;
				return (-1);
			}
		}
		if (check_arg(data, data->commands[idx].args_vec[i], &exp_str) == -1)
			return (0);
		if (exp_str.name)
		{
			in_list = check_if_exist(data->envp, exp_str.name);
			if (in_list)
				env_lst_change_content(in_list, exp_str.content, exp_str.equal);
			else
				env_lst_addfront(&data->envp,
					env_lstnew
					(data, exp_str.name, exp_str.content, exp_str.equal));
		}
		i++;
	}
	find_env_path(data->envp, data);
	return (1);
}
