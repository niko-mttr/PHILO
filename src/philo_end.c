/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:44:38 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/24 18:52:56 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		stop_action(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->mutex_stop);
	if (data->stop == 1)
		i = 1;
	pthread_mutex_unlock(&data->mutex_stop);
	return (i);
}

int	stop_time(t_phil *philo)
{
	int i;

	i = 0;
	pthread_mutex_lock(&philo->mutex_time);
	if (philo->stop_time == 1)
		i = 1;
	pthread_mutex_unlock(&philo->mutex_time);
	return (i);
}

void	ft_stop_signal(t_data *data, int *stop)
{
	int i;

	*stop = 1;
	pthread_mutex_lock(&data->mutex_stop);
	data->stop= 1;
	pthread_mutex_unlock(&data->mutex_stop);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philo[i].mutex_time);
		data->philo[i].stop_time = 1;
		pthread_mutex_unlock(&data->philo[i].mutex_time);
		i++;
	}
}

int	scd_end(t_data *data)
{
	int i;
	int full;
	int stop;

	stop = 0;
	while (1)
	{
		i = -1;
		full = 0;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].checker);
			if (data->philo[i].lim == 0)
				full++;
			if (full == data->nb_philo)
				ft_stop_signal(data, &stop);
			if (data->philo[i].lim != 0 && ft_time_diff(data->philo[i].last_eat) > data->time_to_die)
				ft_message_death(&data->philo[i], "is dead", &stop);
			pthread_mutex_unlock(&data->philo[i].checker);
		}
		if (stop)
		{
			printf("je passe dans ma fin \n\n\n\n\n\n\n");
			break ;
		}
	}
	return (1);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->pid[i], NULL);
		i++;
	}
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->mutex_fork[i]);
		pthread_mutex_destroy(&data->philo[i].checker);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_message);
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_stop);
	if (data->philo)
		free(data->philo);
	if (data->pid)
		free(data->pid);
	if (data->mutex_fork)
		free(data->fork);
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
	// free_all(data);
	// pthread_mutex_destroy(&data->mutex_message);
	exit(EXIT_FAILURE);
}
