/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:20:42 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/22 17:46:54 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->fork[i].use = 0;
		i++;
	}
}

void	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].all_philo = data->nb_philo; 
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->nb_philo;
		data->philo[i].last_eat = get_time();
		data->philo[i].lim = data->nb_full;
		data->philo[i].data = data;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		pthread_mutex_init(&data->philo[i].eater, NULL);
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
}

void	ft_init_data(t_data *data, char **arg)
{
	pthread_mutex_init(&data->mutex_message, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_stop, NULL);
	// pthread_mutex_init(&data->mutex_time, NULL);
	data->nb_philo = ft_atoi(arg[1]);
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
	data->dead_philo = 0;
	data->stop = 0;
	if (arg[5])
		data->nb_full = ft_atoi(arg[5]);
	data->full = 0;
	data->philo = (t_phil *)malloc(sizeof(t_phil) * data->nb_philo);
	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(t_fork) * data->nb_philo);
	data->pid = (pthread_t *)malloc(sizeof(pthread_t) * data->nb_philo);
	// if (!data->philo || !data->fork || !data->pid)
		// free_all(data);
	ft_init_philo(data);
	// ft_init_fork(data);
}
