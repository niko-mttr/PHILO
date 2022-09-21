/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattera <nmattera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:59:40 by nmattera          #+#    #+#             */
/*   Updated: 2022/09/21 19:07:51 by nmattera         ###   ########.fr       */
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

# define RIGHT 1
# define LEFT -1

typedef struct s_phil
{
	int				id;
	pthread_mutex_t	eater;
	int				left_fork;
	int				right_fork;
	int				nb_eat;
	long			last_eat;
	int				lim;
	int				is_dead;
	struct s_data	*data;
}					t_phil;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				use;
}					t_fork;

typedef struct s_data
{
	struct s_phil	*philo;
	struct s_fork	*fork;
	pthread_t		*pid;
	pthread_mutex_t	mutex_message;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t mutex_time;
	int				nb_philo;
	int				dead_philo;
	long			start;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				nb_full;
	int				full;
}					t_data;

/* parsing*/
int					ft_check_num(int ac, char **av);

/* end */
int					scd_end(t_data *data);

void				destroy_all(t_data *data);
int					end_checker(t_data *data);
void				ft_exit_fail(t_data *data, int max);

/* utils */
int					ft_atoi(char *s);
void				free_all(t_data *data);
void				ft_message(t_phil *philo, char *s);
void				ft_message_eat(t_phil *philo, char *s);
void				ft_message_death(t_phil *philo, char *s);

/* time */
long				get_time(void);
long				ft_time_diff(long clock);
void				ft_sleep(t_phil *philo, long end);
void				ft_usleep(long time);
long				ft_time_to_think(t_phil *philo);

/* init */
void				ft_init_data(t_data *data, char **arg);

/* routine */
void				left(t_phil *philo);
void				right(t_phil *philo);

#endif
