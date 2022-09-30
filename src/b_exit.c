/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:31:14 by theodeville       #+#    #+#             */
/*   Updated: 2022/09/30 10:31:28 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

static int	check_sign(int sign)
{
	if (sign < 0)
		return (-1);
	return (0);
}

long long	ft_atol(const char *str)
{
	long long	res;
	long long	neg;
	long long	i;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if ((long long int)res > 9223372036854775807)
			return (-1);
	}
	return (res * neg);
}

// cherche si il y a autre chose qu'un num dans la string
int	no_numeric(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (arg[i] < 48 || arg[i] > 57)
			return (1);
	return (0);
}

int	b_exit(t_data_p *d, int idx)
{
	int	i;

	i = -1;
	if (!strncmp_ncs("exit", d->commands[idx].args_vec[0]))
	{
		while (d->commands[idx].args_vec[++i])
		{
			if (i > 1)
			{
				write(2, "exit: too many arguments\n", 26);
				g_status = 1;
				return (-1);	
			}
		}
		if (d->commands[idx].args_vec[1])
		{
			if (no_numeric(d->commands[idx].args_vec[1])
				|| ft_atol(d->commands[idx].args_vec[1]) == -1)
			{
				write(2, "exit: numeric argument required\n", 32);
				g_status = 255;
			}
			else
				g_status = ft_atol(d->commands[idx].args_vec[1]);
		}
		write(1, "exit\n", 5);
		exit(g_status);
	}
	return (0);
}
