/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:38:12 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/29 14:06:21 by lseeger          ###   ########.fr       */
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

// Number Utils
int						ft_atoi(const char *str);
bool					ft_aisi(char *str);
void					ft_putnbr_fd(int n, int fd);
int						ft_isdigit(int c);

// Str Utils
void					ft_putstr(char *str);
void					ft_putstr_err(char *str);

// Philosopher Struct
typedef struct s_philo	t_philo;

typedef struct s_philosopher
{
	t_philo				*philo;
	int					id;
	int					number_of_meals;
	long long			last_meal_time;

	// thread stuff
	pthread_t			thread;
}						t_philosopher;

typedef struct s_philo
{
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		philo_data_mutex;
	bool				is_running;
	int					number_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	t_philosopher		*philosophers;
}						t_philo;

int						init_philo(t_philo *philo, int argc, char **argv);
int						init_philosophers(t_philo *philo);
void					print_philo(t_philo *philo);
void					free_philo(t_philo *philo);
void					philosopher_routine(t_philosopher *philosopher);

#endif
