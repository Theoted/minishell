/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:29:36 by theodeville       #+#    #+#             */
/*   Updated: 2022/09/28 08:47:52 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

// Creer une variable d'environnement avec un contenu qui pointe sur NULL
int	create_var_no_content(t_data_p *data, char *arg,
	char **content, char **name)
{
	*name = gc_strdup(&data->track, arg);
	*content = NULL;
	return (1);
}

int	check_arg(t_data_p *data, char *arg, char **content, char **name)
{
	int		i;
	t_envp	*tmp;

	i = -1;
	tmp = data->envp;
	if (arg[0] == '=')
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	if (!contains_equal(arg))
	{
		if (!check_if_exist(tmp, arg))
			return (create_var_no_content(data, arg, content, name));
		return (1);
	}
	while (arg[++i] && arg[i] != '=')
		if (arg[i] == ' ')
			return (1);
	*name = gc_substr(&data->track, arg, 0, i);
	*content = remove_quotes(data, gc_substr
		(&data->track, arg, i + 1, ft_strlen(arg) - i));
	return (0);
}

void	init_export_vars(char **content, char **name, t_envp **in_list)
{
	*content = NULL;
	*name = NULL;
	in_list = NULL;
}

int	b_export(t_data_p *data, int idx)
{
	int		i;
	char	*content;
	char	*name;
	t_envp	*in_list;

	i = 1;
	if (!arg_vec_len(data, idx))
		print_export(data->envp);
	while (data->commands[idx].args_vec[i])
	{
		init_export_vars(&content, &name, &in_list);
		check_arg(data, data->commands[idx].args_vec[i], &content, &name);
		if (name)
		{
			in_list = check_if_exist(data->envp, name);
			if (in_list)
				env_lst_change_content(in_list, content);
			else
				env_lst_addfront(&data->envp, env_lstnew(data, name, content));
		}
		i++;
	}
	find_env_path(data->envp, data);
	return (1);
}
