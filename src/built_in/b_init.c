/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:58:40 by theodeville       #+#    #+#             */
/*   Updated: 2022/10/07 01:10:57 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envp	*env_lstlast(t_envp *lst)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_envp	*env_lstnew(t_data *data, char *name, char *content, int equal)
{
	t_envp	*lstnew;

	lstnew = gc_calloc(sizeof(t_envp), 1, &data->track);
	if (!lstnew)
		return (0);
	lstnew->name = name;
	lstnew->content = content;
	lstnew->equal = equal;
	lstnew->next = NULL;
	return (lstnew);
}

// Increment la variable shlvl mais ne fonctionne pas car la liste de var
// s'initialise avec les variables d'env du shell de base
void	update_shlvl(t_data *data, t_envp *node)
{
	int		shlvl;
	char	*tmp;

	tmp = node->content;
	shlvl = ft_atoi(node->content);
	shlvl++;
	tmp = ft_itoa(shlvl);
	node->content = gc_strdup(&data->track, tmp);
	free(tmp);
}

void	env_lstadd_back(t_data *data, t_envp **alst, t_envp *new)
{
	t_envp	*last;

	if (!new || !alst)
		return ;
	if (!strncmp_len(new->name, "SHLVL"))
		update_shlvl(data, new);
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = env_lstlast(*alst);
	last->next = new;
}

void	init_our_envp(t_data *data)
{
	int	i;

	i = 0;
	data->envp = NULL;
	while (data->env_vars[i])
	{
		env_lstadd_back(data, &data->envp, env_lstnew(data,
				gc_split(&data->track, data->env_vars[i], '=')[0],
				gc_split(&data->track, data->env_vars[i], '=')[1],
				1));
		i++;
	}
}
