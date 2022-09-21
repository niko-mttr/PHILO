/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:34:09 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/21 14:09:33 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	last(t_phil *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->id].mutex);
	philo->data->fork[philo->id].use = 1;
	ft_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[0].mutex);
	ft_message(philo, "has taken a fork");
	philo->data->fork[0].use = 1;
	ft_message_eat(philo, "is eating");
	ft_sleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->fork[0].mutex);
	pthread_mutex_unlock(&philo->data->fork[philo->id].mutex);
	philo->data->fork[philo->id].use = 0;
	philo->data->fork[0].use = 0;
}


void	left(t_phil *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork].mutex);
	ft_message(philo, "has taken a fork");
	// philo->data->fork[philo->id].use = 1;
	pthread_mutex_lock(&philo->data->fork[philo->right_fork].mutex);
	ft_message(philo, "has taken a fork");
	// philo->data->fork[philo->id + LEFT].use = 1;
	ft_message_eat(philo, "is eating");
	ft_sleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork].mutex);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork].mutex);
	// philo->data->fork[philo->id].use = 0;
	// philo->data->fork[philo->id + LEFT].use = 0;
}

void	right(t_phil *philo)
{
	if (philo->id != (philo->data->nb_philo))
	{
		pthread_mutex_lock(&philo->data->fork[philo->right_fork].mutex);
		ft_message(philo, "has taken a fork");
		// philo->data->fork[philo->id].use = 1;
		pthread_mutex_lock(&philo->data->fork[philo->left_fork].mutex);
		ft_message(philo, "has taken a fork");
		// philo->data->fork[philo->id + RIGHT].use = 1;
		ft_message_eat(philo, "is eating");
		ft_sleep(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork].mutex);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork].mutex);
			// philo->data->fork[philo->id].use = 0;
			// philo->data->fork[philo->id + RIGHT].use = 0;
	}
	else
		left(philo);
}
