/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:58:40 by theodeville       #+#    #+#             */
/*   Updated: 2022/07/22 12:18:07 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp *env_lstlast(t_envp *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_envp *env_lstnew(t_data_p *data, char *name, char *content)
{
	t_envp *lstnew;

	lstnew = gc_calloc(sizeof(t_envp), 1, &data->track);
	if (!lstnew)
		return (0);
	lstnew->name = name;
	lstnew->content = content;
	lstnew->next = NULL;
	return (lstnew);
}

void env_lstadd_back(t_envp **alst, t_envp *new)
{
	t_envp *last;

	if (!new || !alst)
		return;
	if (!*alst)
	{
		*alst = new;
		return;
	}
	last = env_lstlast(*alst);
	last->next = new;
}

// Cette commande permet de detecter dans chaque command si
// il y a un built in. Si c'est le cas, on execute le built-in
// avec la fonction exec_built_in
int detect_buitins(t_data_p *data)
{
	char *builtins[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"};
	int i;
	int j;

	i = 0;
	while (data->commands[i].stop == 0)
	{
		if (!data->commands[i].args_vec)
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < 7)
		{
			if (!strncmp_len(data->commands[i].args_vec[0], builtins[j]))
				exec_built_ins(data, i, builtins[j]);
			j++;
		}
		i++;
	}
	return (0);
}

void init_our_envp(t_data_p *data)
{
	int i;

	i = 0;
	data->envp = NULL;
	while (data->env_vars[i])
	{
		env_lstadd_back(&data->envp, env_lstnew(data,
												gc_split(&data->track, data->env_vars[i], '=')[0],
												gc_split(&data->track, data->env_vars[i], '=')[1]));
		i++;
	}
}