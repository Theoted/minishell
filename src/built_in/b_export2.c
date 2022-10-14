/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 09:58:01 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/14 04:18:23 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export_fd_out(t_data *data, t_envp *envp, int idx)
{
	t_envp	*tmp;
	tmp = envp;
	while (tmp)
	{
		write(data->commands[idx].fd_out,"declare -x ", 11);
		write(data->commands[idx].fd_out, tmp->name, ft_strlen(tmp->name));
		if (tmp->content)
		{
			write(data->commands[idx].fd_out,"=\"", 2);
			write(data->commands[idx].fd_out, tmp->content, ft_strlen(tmp->content));
			write(data->commands[idx].fd_out,"\"", 1);
		}
		else if (tmp->equal)
			write(data->commands[idx].fd_out, "=\"\"", 3);
		write(data->commands[idx].fd_out,"\n", 1);
		tmp = tmp->next;
	}
	// if (!data->commands[idx + 1].stop && data->pipes_nb > 0)
	// 	exit(0);
}

void	print_export(t_data *data, t_envp *envp, int idx)
{
	(void)data;
	(void)idx;
	t_envp	*tmp;
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
	// if (!data->commands[idx + 1].stop && data->pipes_nb > 0)
	// 	exit(0);
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
