/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:44:38 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/21 19:20:27 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_dead_check(t_data *data)
{
	int		i;
	long	time_to_die;

	i = 0;
	time_to_die = data->time_to_die;
	while (i < data->nb_philo)
	{
		if (ft_time_diff(data->philo[i].last_eat) > time_to_die)
		{
			data->dead_philo = 1;
			ft_message_death(&data->philo[i], "is died");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_full_check(t_data *data)
{
	int	i;
	int	all_full;

	i = 0;
	all_full = 1;
	while (i < data->nb_philo)
	{
		if (data->philo[i].lim > 0 || data->philo[i].lim < 0)
			all_full = 0;
		i++;
	}
	if (all_full == 1)
		data->full = 1;
	return (all_full);
}

int	ft_unlock_mutex(t_data *data, int i)
{
	pthread_mutex_unlock(&data->mutex_message);
	pthread_mutex_unlock(&data->philo[i].eater);
	return (0);
}

int	scd_end(t_data *data)
{
	int i;
	int full;

	while (1)
	{
		i = 0;
		full = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].eater);
			pthread_mutex_lock(&data->mutex_message);
			if (data->philo[i].lim == 0)
				full++;
			if (full == data->nb_philo)
				return (ft_unlock_mutex(data, i));
			if (data->philo[i].lim != 0 && ft_time_diff(data->philo[i].last_eat) > data->time_to_die)
				return (ft_unlock_mutex(data, i));
			// ft_usleep(200);
			pthread_mutex_unlock(&data->mutex_message);
			pthread_mutex_unlock(&data->philo[i].eater);
			i++;
		}
	}
}

int	end_checker(t_data *data)
{
	while (1)
	{
		if (ft_dead_check(data))
			return (0);
		if (ft_full_check(data))
			return (0);
	}
	return (1);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		// pthread_join(data->pid[i], NULL);
		pthread_detach(data->pid[i]);
		// pthread_mutex_destroy(&data->fork[i].mutex);
		i++;
	}
	free_all(data);
	// pthread_mutex_destroy(&data->mutex_message);
}

void	ft_exit_fail(t_data *data, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_join(data->pid[i], NULL);
		// pthread_detach(data->pid[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		// pthread_mutex_destroy(&data->fork[i].mutex);
		i++;
	}
	free_all(data);
	// pthread_mutex_destroy(&data->mutex_message);
	exit(EXIT_FAILURE);
}
