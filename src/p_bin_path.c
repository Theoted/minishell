/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_bin_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:28:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/27 10:13:24 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction trouve la variable d'environnement PATH
// et la split dans env_path (structure t_args)
int	find_env_path(t_envp *envp, t_data_p *data)
{
	int		i;
	char	*path;

	i = -1;
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
char	*expend_env_var(t_data_p *data, t_envp *envp, char *var)
{
	int		i;
	char	*env_var;

	i = -1;
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

// Cette fonction recupere la commande en raw et la split
// dans la structure command pour la var arg_vec
int	get_cmd_in_arg(char *arg, t_data_p *data, int idx)
{
	char	*cmd;

	cmd = skip_in_out_hd(arg, data);
	if (cmd)
		data->commands[idx].args_vec = gc_split_spaces(&data->track, cmd, ' ');
	else
		data->commands[idx].args_vec = NULL;
	return (0);
}
