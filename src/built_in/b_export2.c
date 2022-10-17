/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 09:58:01 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/17 15:50:18 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export_fd_out(t_data *data, t_envp *envp, int idx)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		write(data->commands[idx].fd_out, "declare -x ", 11);
		write(data->commands[idx].fd_out, tmp->name, ft_strlen(tmp->name));
		if (tmp->content)
		{
			write(data->commands[idx].fd_out, "=\"", 2);
			write(data->commands[idx].fd_out,
				tmp->content, ft_strlen(tmp->content));
			write(data->commands[idx].fd_out, "\"", 1);
		}
		else if (tmp->equal)
			write(data->commands[idx].fd_out, "=\"\"", 3);
		write(data->commands[idx].fd_out, "\n", 1);
		tmp = tmp->next;
	}
}

void	print_export(t_data *data, t_envp *envp, int idx)
{
	t_envp	*tmp;

	(void)data;
	(void)idx;
	tmp = envp;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->content)
			printf("=\"%s\"", tmp->content);
		else if (tmp->equal)
			printf("=\"\"");
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

void	env_lst_change_content(t_envp *node, char *content, int equal)
{
	if (!node)
		return ;
	node->content = content;
	node->equal = equal;
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
