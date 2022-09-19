/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:09:32 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/19 15:51:03 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || (c == ' '))
		return (1);
	return (0);
}

int ft_check_max(char *s)
{
	int i;
	long max;

	i = 0;
	while(s[i])
		i++;
	if (i > 10)
		return (0);
	max = ft_atoi(s);
	if (max > 2147483647 || max < 0)
		return (0);
	return (1);
}

int	ft_check_num(int ac, char **av)
{
	int	arg;
	int i;

	arg = 1;
	while (av[arg])
	{
		i = 0;
		while (av[arg][i])
		{
			if (!is_num(av[arg][i]) && !is_space(av[arg][i]))
				return (0);
			i++;
		}
		if (!ft_check_max(av[arg]))
			return (0);
		if (arg == 1 && !ft_atoi(av[arg]))
			return (0);
		if (ac == 6 && arg == 5 && !ft_atoi(av[arg]))
			return (0);
		arg++;
	}
	return (1);
}
