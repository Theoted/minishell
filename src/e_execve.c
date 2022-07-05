/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:08:33 by pat               #+#    #+#             */
/*   Updated: 2022/07/05 14:40:20 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	e_execve(t_commands *c)
{
	if (execve(c->cmd_path, c->args_vec, c->envp) == -1)
	{
		write(2, "bash: ", 6);
		write(2, c->args_vec[0], ft_strlen(c->args_vec[0]));
		write(2, ": command not found\n", 21);
	}
}
