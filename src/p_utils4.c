/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:55:02 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/04 13:27:59 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

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
	printf("export: `%s': not a valid identifier\n", arg);
	return (1);
}
