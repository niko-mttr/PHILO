/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:44:38 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/22 17:16:47 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		death(t_data *data)
{
	pthread_mutex_lock(&data->mutex_death);
	if (data->dead_philo == 1)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_death);
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
			if (data->philo[i].lim == 0)
				full++;
			if (full == data->nb_philo)
				return (0);
			if (data->philo[i].lim != 0 && ft_time_diff(data->philo[i].last_eat) > data->time_to_die)
				return (ft_message_death(&data->philo[i], "is dead"));
			pthread_mutex_unlock(&data->philo[i].eater);
			// ft_usleep(100);
			i++;
		}
	}
	return (1);
}

void	free_all(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->pid)
		free(data->pid);
	if (data->fork)
		free(data->fork);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		// pthread_mutex_destroy(&data->philo[i].eater);
		// pthread_mutex_destroy(&data->mutex_fork[i]);
		pthread_join(data->pid[i], NULL);
		i++;
	}
	// pthread_mutex_destroy(&data->mutex_message);
	// pthread_mutex_destroy(&data->mutex_death);
	free_all(data);
}

void	ft_exit_fail(t_data *data, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_join(data->pid[i], NULL);
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
