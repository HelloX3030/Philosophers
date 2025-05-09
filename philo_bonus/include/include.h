/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello_x <hello_x@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:38:12 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/09 16:39:57 by hello_x          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
#define INCLUDE_H

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define WAIT_MONITORING 9000
#define WAIT_PHILOSOPHER 1000
#define WAIT_USLEEP 50

// Number Utils
int ft_atoi(const char *str);
bool ft_aisi(char *str);
int ft_isdigit(int c);

// Philosopher Struct
typedef struct s_philo t_philo;

typedef struct s_philosopher
{
	t_philo *philo;
	int id;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

	// Philo Data
	pthread_mutex_t data_mutex;
	int number_of_meals;
	struct timeval last_meal;
} t_philosopher;

typedef struct s_philo
{
	struct timeval start_time;
	pthread_mutex_t write_mutex;
	pthread_mutex_t is_running_mutex;
	bool is_running;
	int number_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_meals;
	t_philosopher *philosophers;
	pthread_mutex_t *forks;
	pthread_t monitoring_thread;
} t_philo;

// wait Functions
void custom_usleep(long long time_in_ms);
long long get_elapsed_time(struct timeval *start_time);
long long get_time_diff_ms(struct timeval *start_time,
						   struct timeval *end_time);
long long get_time_diff_micro(struct timeval *start_time,
							  struct timeval *end_time);

// philo Functions
int init_philo(t_philo *philo, int argc, char **argv);
int init_philosophers(t_philo *philo);
void free_philo(t_philo *philo);
void philosopher_wait(t_philosopher *philosopher, int time);
void philosopher_routine(t_philosopher *philosopher);
void monitoring(t_philo *philo);

// Philosopher Routine Utils
void print_message(t_philosopher *philosopher,
				   char *message);

#endif
