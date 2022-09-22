/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:15:30 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/22 17:17:57 by nmattera         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->eater);
	philo->last_eat = get_time();
		if (philo->lim > 0)
			philo->lim--;
	pthread_mutex_unlock(&philo->eater);
	ft_usleep(philo->time_to_eat);
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
	pthread_mutex_lock(&philo->eater);
	philo->last_eat = get_time();
	if (philo->lim > 0)
		philo->lim--;
	pthread_mutex_unlock(&philo->eater);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right_fork]);
}

void	*process_philo(void *data)
{
	t_phil	*philo;

	philo = (t_phil *)data;
	if (!philo->id % 2)
		ft_usleep(2);
	while (!death(philo->data))
	{
		if (!(philo->id % 2) && philo->id != philo->all_philo)
			right(philo);
		else
			left(philo);
		ft_message(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		ft_message(philo, "is thinking");
		ft_usleep(ft_time_to_think(philo));
		if (philo->lim == 0)
			break;
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
	while (i < data.nb_philo)
	{
		if (pthread_create(&data.pid[i], NULL, &process_philo, &data.philo[i]))
			ft_exit_fail(&data, i + 1);
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
