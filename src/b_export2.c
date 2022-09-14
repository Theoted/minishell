/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 09:58:01 by tdeville          #+#    #+#             */
/*   Updated: 2022/09/14 14:53:40 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->content)
			printf("=\"%s\"", tmp->content);
		printf("\n");
		tmp = tmp->next;
	}
}

void	env_lst_addfront(t_envp **alst, t_envp *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

void	env_lst_change_content(t_envp *node, char *content)
{
	if (!node)
		return ;
	node->content = content;
}

t_envp	*check_if_exist(t_envp *alst, char *name)
{
	while (alst)
	{
		if (!strncmp_len(alst->name, name))
			return (alst);
		alst = alst->next;
	}
	return (NULL);
}
