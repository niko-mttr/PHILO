/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:15:43 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/26 17:21:09 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *s)
{
	long	n;
	int		minus;
	int		i;

	minus = 1;
	n = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			minus = -1;
		i++;
	}
	while (s[i])
	{
		n = n * 10 + s[i] - '0';
		i++;
	}
	return (n * minus);
}

void	ft_message(t_phil *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_message);
	if (!stop_action(philo->data))
		printf("%ld %d %s\n", ft_time_diff(philo->data->start), philo->id, s);
	pthread_mutex_unlock(&philo->data->mutex_message);
}

void	ft_message_death(t_phil *philo, char *s, int *stop)
{
	pthread_mutex_lock(&philo->data->mutex_message);
	if (!stop_action(philo->data))
		printf("%ld %d %s\n", ft_time_diff(philo->data->start), philo->id, s);
	pthread_mutex_unlock(&philo->data->mutex_message);
	ft_stop_signal(philo->data, stop);
}

void	ft_free_all(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->pid)
		free(data->pid);
	if (data->mutex_fork)
		free(data->mutex_fork);
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->mutex_fork[i]);
		pthread_mutex_destroy(&data->philo[i].checker);
		pthread_mutex_destroy(&data->philo[i].mutex_time);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_message);
	pthread_mutex_destroy(&data->mutex_stop);
}
