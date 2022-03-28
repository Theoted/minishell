/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_bin_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:28:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/21 10:07:09 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction trouve la variable d'environnement PATH
// et la split dans env_path (structure t_args)
int	find_env_path(char **envp, t_data_p *data)
{
	int		i;
	char	*path;
	
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

char	*expend_env_var(t_data_p *data, char **envp, char *var)
{
	int		i;
	char	*env_var;
	char	*tmp;

	
	i = -1;
	tmp = gc_strjoin(&data->track, var, "=");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], tmp, ft_strlen(tmp)))
		{
			env_var = gc_substr(&data->track, envp[i], ft_strlen(tmp), ft_strlen(envp[i]));
			gc_free_malloc(&data->track, (void **)&tmp);
			return (env_var);
		}
	}
	gc_free_malloc(&data->track, (void **)&tmp);
	return (var);
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
int	ft_access(char *arg)
{
	if (!access(arg, X_OK))
		if (!access(arg, R_OK | W_OK))
			return (1);
	return (0);
}
