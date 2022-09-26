/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:15:30 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/26 16:48:12 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	left(t_phil *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]);
	ft_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]);
	ft_message(philo, "has taken a fork");
	ft_message(philo, "is eating");
	pthread_mutex_lock(&philo->checker);
	philo->last_eat = get_time();
		if (philo->lim > 0)
			philo->lim--;
	pthread_mutex_unlock(&philo->checker);
	ft_sleep_check(philo, philo->time_to_eat);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
}

void	right(t_phil *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->right_fork]);
	ft_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]);
	ft_message(philo, "has taken a fork");
	ft_message(philo, "is eating");
	pthread_mutex_lock(&philo->checker);
	philo->last_eat = get_time();
	if (philo->lim > 0)
		philo->lim--;
	pthread_mutex_unlock(&philo->checker);
	ft_sleep_check(philo, philo->time_to_eat);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
}

void	*process_philo(void *data)
{
	t_phil	*philo;

	philo = (t_phil *)data;
	if (!philo->id % 2)
		ft_sleep_check(philo, ft_time_to_think(philo));
	while (!stop_action(philo->data))
	{
		if (!(philo->id % 2) && philo->id + 1 != philo->all_philo)
			right(philo);
		else
			left(philo);
		ft_message(philo, "is sleeping");
		ft_sleep_check(philo, philo->time_to_sleep);
		ft_message(philo, "is thinking");
		ft_sleep_check(philo, ft_time_to_think(philo));
	}
	return (NULL);
}

int	start_philo(char **arg)
{
	t_data	data;
	int		i;

	ft_init_data(&data, arg);
	i = 0;
	data.start = get_time();
	if (data.nb_philo == 1)
		return (solo_philo(data));
	while (i < data.nb_philo)
	{
		if (pthread_create(&data.pid[i], NULL, &process_philo, &data.philo[i]))
		{
			ft_free_all(&data);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (!scd_end(&data))
		destroy_all(&data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("too many or not enough arguments\n");
		exit(EXIT_FAILURE);
	}
	if (!ft_check_num(ac, av))
	{
		printf("Invalid argument\n");
		exit(EXIT_FAILURE);
	}
	if (start_philo(av))
		exit (EXIT_FAILURE);
	return (0);
}
