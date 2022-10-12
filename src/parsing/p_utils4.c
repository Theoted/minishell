/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmattheo <rmattheo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:55:02 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/12 20:50:17 by rmattheo         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	free_all(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free (arg);
}

void	remove_quote_init(t_echo *data, char *arg)
{
	data->new = NULL;
	data->quote = 0;
	data->arg = arg;
}

int	double_arr_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	exit_error_avlen(void)
{
	write(2, "exit: too many arguments\n", 26);
	g_status = 1;
	return (-1);
}

int	export_error_arg(char *arg)
{
	write(2, "export: '", 10);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	g_status = 1;
	return (1);
}
