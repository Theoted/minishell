/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_bin_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:28:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/19 15:10:45 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction trouve la variable d'environnement PATH
// et la split dans env_path (structure t_args)
int find_env_path(char **envp, t_data_p *data)
{
	int i;
	char *path;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = gc_substr(&data->track, envp[i], 5, ft_strlen(&envp[i][5]));
			data->env_path = gc_split(&data->track, path, ':');
			return (0);
		}
	}
	return (1);
}

// Permet d'expend les variables d'envrionnement si elles existes
// Si elle existe la fonction renvoie la variable, sinon elle ne renvoie rien
char *expend_env_var(t_data_p *data, t_envp *envp, char *var)
{
	int i;
	char *env_var;

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
char *get_cmd_in_arg(char *arg, t_data_p *data, int idx)
{
	char	*cmd;

	cmd = skip_in_out_hd(arg, data);
	if (cmd)
		data->commands[idx].args_vec = gc_split_spaces(&data->track, cmd, ' ');
	else
		data->commands[idx].args_vec = NULL;
	return (0);
}

// Cette fonction est la fonction principale de parsing de l'argument,
// pour trouver la commande outre les <, <<, >, >> 
char *skip_in_out_hd(char *arg, t_data_p *data)
{
	int i;
	int check;
	char *cmd;

	i = -1;
	check = 0;
	cmd = NULL;
	while (arg[++i])
	{
		if (arg[i] == ' ')
			skip_spaces(arg, &i);
		else if (arg[i] == '<')
			skip_in_hd(arg, &i);
		else if (arg[i] == '>')
			skip_out(arg, &i);
		else
		{
			cmd = get_cmd(arg, i, data);
			break;
		}
	}
	return (cmd);
}

// Cette fonction skip les < et <<
void skip_in_hd(char *arg, int *i)
{
	if (arg[*i + 1] == '<')
		(*i)++;
	(*i)++;
	skip_spaces(arg, i);
	while (arg[*i] != ' ' && arg[*i] != '>' && arg[*i])
		(*i)++;
}

// Cette fonction skip les > et >>
void skip_out(char *arg, int *i)
{
	if (arg[*i + 1] == '>')
		(*i)++;
	(*i)++;
	skip_spaces(arg, i);
	while (arg[*i] != ' ' && arg[*i] != '<' && arg[*i])
		(*i)++;
}

// Cette fonction skip les espaces
void skip_spaces(char *arg, int *i)
{
	while (arg[*i] == ' ' && arg[*i] && !state_checker(arg, 0, *i))
		(*i)++;
}

// Cette fonction recupere la commande
char *get_cmd(char *arg, int i, t_data_p *data)
{
	int j;
	int t;
	int check;

	j = 0;
	check = 0;
	while (arg[i + j] && arg[i + j] != '<' && arg[i + j] != '>')
		j++;
	return (gc_substr(&data->track, arg, i, j));
}

// Cette fonction sert a trouver le path d'un bin et de verifier si
// il possede les droits

// int	find_bin_path(t_args *args)
// {
// 	int		i;
// 	char	*str;
// 	char	*env_path_slash;

// 	i = 0;
// 	while (args->env_path[i])
// 	{
// 		env_path_slash = ft_strjoin(args->env_path[i], "/");
// 		str = ft_strjoin(env_path_slash)
// 		if (ft_access())
// 	}
// }

// Cette fonction check si le path envoyé existe et possède les droits
int ft_access(char *arg)
{
	if (!access(arg, X_OK))
		if (!access(arg, R_OK | W_OK))
			return (1);
	return (0);
}
