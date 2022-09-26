/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_solo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:37:21 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/26 17:13:54 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*process_philo_solo(void *data)
{
	t_phil	*philo;

	philo = (t_phil *)data;
	ft_message(philo, "has taken a fork");
	ft_usleep(philo->time_to_die);
	ft_message(philo, "died");
	return (NULL);
}

int	solo_philo(t_data data)
{
	if (pthread_create(&data.pid[0], NULL, &process_philo_solo, &data.philo[0]))
	{
		ft_free_all(&data);
		return (EXIT_FAILURE);
	}
	destroy_all(&data);
	return (0);
}
