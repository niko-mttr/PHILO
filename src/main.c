/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:15:30 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/16 11:56:04 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*process_philo(void *data)
{
	t_phil	*philo;

	philo = (t_phil *)data;
	while (1)
	{
		if (!(philo->id % 2) && !philo->data->dead_philo)
			right(philo);
		else if (!philo->data->dead_philo)
			left(philo);
		ft_message(philo, "is sleeping");
		ft_sleep(philo, philo->data->time_to_sleep);
		ft_message(philo, "is thinking");
		// ft_sleep(philo, ft_time_to_think(philo));
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
		if (i % 2)
			my_sleep(1);
		if (pthread_create(&data.pid[i], NULL, process_philo, &data.philo[i]))
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
	if (!ft_check_num(av))
	{
		printf("Use only numeric characters\n");
		exit(EXIT_FAILURE);
	}
	start_philo(av);
}
