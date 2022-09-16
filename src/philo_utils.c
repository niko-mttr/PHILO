/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:15:43 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/16 11:44:38 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *s)
{
	long	n;
	int	minus;
	int	i;

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

void	free_all(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->pid)
		free(data->pid);
	if (data->fork)
		free(data->fork);
}

void	ft_message(t_phil *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_message);
	if (!philo->data->dead_philo)
		printf("%ld %d %s\n", ft_time_diff(philo->data->start), philo->id + 1, s);
	pthread_mutex_unlock(&philo->data->mutex_message);
}

void	ft_message_eat(t_phil *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_message);
	if (!philo->data->dead_philo)
	{
		printf("%ld %d %s\n", ft_time_diff(philo->data->start), philo->id + 1, s);
		philo->last_eat = get_time();
		if (philo->lim > 0)
			philo->lim--;
	}
	pthread_mutex_unlock(&philo->data->mutex_message);
}

void	ft_message_death(t_phil *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_message);
	printf("%ld %d %s\n", ft_time_diff(philo->data->start), philo->id + 1, s);
	pthread_mutex_unlock(&philo->data->mutex_message);
}