/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:31:14 by theodeville       #+#    #+#             */
/*   Updated: 2022/10/06 08:06:19 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	check_lld(char *arg)
{
	int		i;
	char	*lld;

	i = -1;
	//TODO: utiliser limits.h et utiliser constante genre LONG_MAX
	lld = "9223372036854775807";
	if (ft_strlen(arg) < 19)
		return (1);
	if (arg[0] == '-')
	{
		lld = "-9223372036854775808";
		i = 0;
	}
	while (arg[++i])
	{
		if (arg[i] > lld[i])
			return (0);
	}
	return (1);
}

long long	ft_atol(const char *str)
{
	unsigned long long int	res;
	unsigned long long int	neg;
	unsigned long long int	i;

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
		if (res > 9223372036854775807)
			return (-1);
	}
	return (res * neg);
}

// cherche si il y a autre chose qu'un num dans la string
// return 0 si il y a que des chiffre
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
		if (double_arr_len(d->commands[idx].args_vec) > 2
			&& !no_numeric(d->commands[idx].args_vec[1]))
			return (exit_error_avlen());
		if (d->commands[idx].args_vec[1])
		{
			if ((no_numeric(d->commands[idx].args_vec[1])
					&& d->commands[idx].args_vec[1][0] != '-')
				|| !check_lld(d->commands[idx].args_vec[1]))
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
