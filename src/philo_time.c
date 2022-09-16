/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:09:51 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/15 16:24:18 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long	ft_time_diff(long clock)
{
	long	diff;

	diff = get_time() - clock;
	return (diff);
}

void	ft_sleep(t_phil *philo, long end)
{
	long	wake_up;

	wake_up = end + get_time();
	while (get_time() < wake_up)
	{
		if (philo->data->dead_philo)
			break ;
		usleep(100);
	}
}

void	my_sleep(long end)
{
	long	wake_up;

	wake_up = end + get_time();
	while (get_time() < wake_up)
		usleep(100);
}

long	ft_time_to_think(t_phil *philo)
{
	long	time_to_think;
	long	last_eat;
	long	time;

	time = get_time();
	last_eat = philo->last_eat;
	time_to_think = (philo->data->time_to_die - (time - last_eat)
			- philo->data->time_to_eat) / 2;
	return (time_to_think);
}
