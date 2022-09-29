/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:39:30 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/28 13:29:36 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Cette fonction permet de savoir si on est dans des guillemets
// Renvoie 0 si on est pas dans un quote
int	state_checker(char *str, int start, int len)
{
	int	i;
	int	quote;

	i = start;
	quote = 0;
	while (str[i] && i < len)
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote && quote != 0)
			quote = 0;
		i++;
	}
	return (quote);
}

// Cette fonction permet de savoir le dernier infile dans l'ordre
// < ou <<
int	last_in_redir(char *arg)
{
	int	check;
	int	i;

	check = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '<')
		{
			if (arg[i + 1] == '<')
			{
				check = 2;
				i++;
			}
			else
				check = 1;
		}
	}
	return (check);
}

int	find_char(char *arg, char c)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == c)
			return (1);
	}
	return (0);
}

int	env_lstsize(t_envp *lst)
{
	int	count;

	count = 0;
	if (lst)
	{
		while (lst)
		{
			count++;
			lst = lst->next;
		}
	}
	return (count);
}

// Fonction qui convertis le tabl envp en double tableau
char	**convert_envp(t_data_p *data, t_envp *envp)
{
	t_envp	*tmp;
	char	**envp2;
	char	*tmp1;
	int		i;

	tmp = envp;
	tmp1 = NULL;
	envp2 = gc_calloc(env_lstsize(envp) + 1, sizeof(char *), &data->track);
	i = 0;
	if (!envp)
		return (envp2);
	while (envp)
	{
		tmp1 = gc_strjoin(&data->track,
			gc_strjoin(&data->track, envp->name, "="), envp->content);
		envp2[i] = gc_strdup(&data->track, tmp1);
		i++;
		envp = envp->next;
	}
	envp2[i] = NULL;
	return (envp2);
}
