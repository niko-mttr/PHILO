/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:09:51 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/19 14:33:16 by nmattera         ###   ########.fr       */
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

void	ft_usleep(long time)
{
	long	alarm;

	alarm = get_time() + time;
	while (get_time() < alarm)
		usleep(time);
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
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	return (time_to_think);
}
