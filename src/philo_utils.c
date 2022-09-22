/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:15:43 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/22 17:46:34 by nmattera         ###   ########.fr       */
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

void	ft_message(t_phil *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_message);
	if (!stop(philo->data))
		printf("%ld %d %s\n", ft_time_diff(philo->data->start), philo->id, s);
	pthread_mutex_unlock(&philo->data->mutex_message);
}


int	ft_message_death(t_phil *philo, char *s)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	philo->data->stop= 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	pthread_mutex_unlock(&philo->eater);
	pthread_mutex_lock(&philo->data->mutex_death);
	philo->data->dead_philo = 1;
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_lock(&philo->data->mutex_message);
	printf("%ld %d %s\n", ft_time_diff(philo->data->start), philo->id, s);
	pthread_mutex_unlock(&philo->data->mutex_message);
	return (0);
}