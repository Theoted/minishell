/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_bin_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:28:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/10 11:49:07 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Cette fonction trouve la variable d'environnement PATH
// et la split dans env_path (structure t_args)
int	find_env_path(t_envp *envp, t_data *data)
{
	char	*path;

	path = NULL;
	while (envp)
	{
		if (!strncmp_len(envp->name, "PATH"))
		{
			path = gc_strdup(&data->track, envp->content);
			data->env_path = gc_split(&data->track, path, ':');
			return (0);
		}
		envp = envp->next;
	}
	if (!path)
		data->env_path = NULL;
	return (1);
}

// Permet d'expend les variables d'envrionnement si elles existes
// Si elle existe la fonction renvoie la variable, sinon elle ne renvoie rien
char	*expend_env_var(t_envp *envp, char *var)
{
	char	*env_var;

	while (envp)
	{
		if (!strncmp_len(envp->name, var))
		{
			env_var = envp->content;
			return (env_var);
		}
		envp = envp->next;
	}
	return (var);
}

int	remove_export_content_quotes(t_data *data, char *arg)
{
	int		i;
	int		j;
	char	*content;

	i = -1;
	j = 0;
	content = NULL;
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			while (arg[i + j])
				j++;
			content = gc_substr(&data->track, arg, i + 1, j);
			content = remove_quotes(data, content);
			break ;
		}
	}
	return (0);
}

int	remove_quotes_arg_vec(t_data *data, char **arg_vec)
{
	int		i;

	i = -1;
	if (!arg_vec)
		return (1);
	while (arg_vec[++i])
	{
		if (strncmp_ncs(arg_vec[0], "echo"))
			arg_vec[i] = remove_quotes(data, arg_vec[i]);
	}
	return (0);
}

// Cette fonction recupere la commande en raw et la split
// dans la structure command pour la var arg_vec
int	get_cmd_in_arg(char *arg, t_data *data, int idx)
{
	char	*cmd;
	int		i;

	i = -1;
	cmd = skip_in_out_hd(arg, data);
	if (cmd)
		data->commands[idx].args_vec = gc_split_spaces(&data->track, cmd, ' ');
	else
		data->commands[idx].args_vec = NULL;
	if (data->commands[idx].args_vec)
		while (data->commands[idx].args_vec[++i])
			data->commands[idx].args_vec[i] = get_echo_env_var
				(data, data->commands[idx].args_vec[i]);
	if (remove_quotes_arg_vec(data, data->commands[idx].args_vec))
		return (1);
	if (!strncmp_ncs(data->commands[idx].args_vec[0], "echo"))
		data->commands[idx].echo_arg_nb
			= echo_arg_nb(data->commands[idx].args_vec);
	printf("arg = %s\n", data->commands[idx].args_vec[0]);
	return (0);
}
