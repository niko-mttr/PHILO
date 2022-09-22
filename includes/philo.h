/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:59:40 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/22 18:37:41 by nmattera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <unistd.h>

# define RIGHT 1
# define LEFT -1

typedef struct s_phil
{
	pthread_mutex_t	eater;
	int				id;
	int				all_philo;
	int				left_fork;
	int				right_fork;
	long			last_eat;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				lim;
	struct s_data	*data;
}					t_phil;

typedef struct s_fork
{
	int				use;
}					t_fork;

typedef struct s_data
{
	struct s_phil	*philo;
	struct s_fork	*fork;
	pthread_t		*pid;
	pthread_mutex_t	mutex_message;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	*mutex_fork;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				nb_philo;
	int				dead_philo;
	long			start;
	int				stop;
	int				nb_full;
	int				full;
}					t_data;

/* parsing*/
int					ft_check_num(int ac, char **av);

/* end */
int					stop(t_data *data);
int					death(t_data *data);
int					scd_end(t_data *data);

void				destroy_all(t_data *data);
int					end_checker(t_data *data);
void				ft_exit_fail(t_data *data, int max);

/* utils */
int					ft_atoi(char *s);
void				free_all(t_data *data);
void				ft_message(t_phil *philo, char *s);
int					ft_message_death(t_phil *philo, char *s);

/* time */
long				get_time(void);
long				ft_time_diff(long clock);
void				ft_sleep_check(t_phil *philo, long end);
void				ft_usleep(long time);
long				ft_time_to_think(t_phil *philo);

/* init */
void				ft_init_data(t_data *data, char **arg);

/* routine */
void				left(t_phil *philo);
void				right(t_phil *philo);

#endif
