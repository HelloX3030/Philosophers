/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:38:12 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/06 16:24:41 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WAIT_INTERVALL 1000

// Number Utils
int						ft_atoi(const char *str);
bool					ft_aisi(char *str);
int						ft_isdigit(int c);

// Str Utils
void					ft_putstr(char *str);
void					ft_putstr_err(char *str);
void					ft_putnbr_fd(int n, int fd);
void					ft_putnbr_long_long_fd(long long n, int fd);

// Philosopher Struct
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	bool				is_taken;
}						t_fork;

typedef struct s_philosopher
{
	t_philo				*philo;
	int					id;
	int					number_of_meals;
	pthread_mutex_t		last_meal_time_mutex;
	struct timeval		last_meal;
	pthread_t			thread;
	t_fork				*left_fork;
	t_fork				*right_fork;
}						t_philosopher;

typedef struct s_philo
{
	struct timeval		start_time;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		is_running_mutex;
	bool				is_running;
	int					number_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	t_philosopher		*philosophers;
	t_fork				*forks;
	pthread_t			monitoring_thread;
}						t_philo;

int						init_philo(t_philo *philo, int argc, char **argv);
int						init_philosophers(t_philo *philo);
void					free_philo(t_philo *philo);
bool					philosopher_finished(t_philosopher *philosopher);
void					philosopher_wait(t_philosopher *philosopher, int time);
void					philosopher_routine(t_philosopher *philosopher);
long long				get_elapsed_time(struct timeval *start_time);
long long				get_time_diff(struct timeval *start_time,
							struct timeval *end_time);
void					monitoring(t_philo *philo);

// Philosopher Routine Utils
void					take_fork(t_philosopher *philosopher, t_fork *fork);
void					think_before_take_fork(t_philosopher *philosopher);
void					release_fork(t_fork *fork);
void					no_fork_found(t_philosopher *philosopher);

#endif
