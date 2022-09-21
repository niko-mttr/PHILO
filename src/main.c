/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:15:30 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/19 16:50:00 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*process_philo(void *data)
{
	t_phil	*philo;

	philo = (t_phil *)data;
	if (philo->id % 2)
		ft_usleep(2);
	while (!philo->data->dead_philo && !philo->data->full)
	{
		if (!(philo->id % 2) && !philo->data->dead_philo && !philo->data->full)
			right(philo);
		else if (!philo->data->dead_philo && !philo->data->full)
			left(philo);
		if (!philo->data->dead_philo && !philo->data->full)
			ft_message(philo, "is sleeping");
		ft_sleep(philo, philo->data->time_to_sleep);
		if (!philo->data->dead_philo && !philo->data->full)
			ft_message(philo, "is thinking");
		ft_sleep(philo, ft_time_to_think(philo));
		if (philo->lim == 0)
			break;
	}
	return (NULL);
}

void	start_philo(char **arg)
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
	if (end_checker(&data))
		destroy_all(&data);
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
	start_philo(av);
}
