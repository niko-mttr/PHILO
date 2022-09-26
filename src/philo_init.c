/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:20:42 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/26 17:04:09 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_fork(t_phil *philo)
{
	philo->left_fork = philo->id - 1;
	philo->right_fork = philo->id % philo->all_philo;
	if ((philo->all_philo == 3))
	{
		if (!(philo->id % 2))
		{
			philo->left_fork = philo->id % philo->all_philo;
			philo->right_fork = philo->id - 1;
		}
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
		data->philo[i].stop_time = 0;
		data->philo[i].last_eat = get_time();
		data->philo[i].lim = data->nb_full;
		data->philo[i].data = data;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		pthread_mutex_init(&data->philo[i].mutex_time, NULL);
		pthread_mutex_init(&data->philo[i].checker, NULL);
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		ft_init_fork(&data->philo[i]);
		i++;
	}
}

void	ft_init_data(t_data *data, char **arg)
{
	pthread_mutex_init(&data->mutex_message, NULL);
	pthread_mutex_init(&data->mutex_stop, NULL);
	data->nb_philo = ft_atoi(arg[1]);
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
	data->stop = 0;
	if (arg[5])
		data->nb_full = ft_atoi(arg[5]);
	data->philo = (t_phil *)malloc(sizeof(t_phil) * data->nb_philo);
	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(t_fork)
			* data->nb_philo);
	data->pid = (pthread_t *)malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->philo || !data->fork || !data->pid)
		ft_free_all(data);
	ft_init_philo(data);
}
