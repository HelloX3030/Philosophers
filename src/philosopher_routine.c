/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:37 by hello_x           #+#    #+#             */
/*   Updated: 2025/05/07 16:12:30 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	think_until_fork(t_philosopher *philosopher, pthread_mutex_t *fork)
{
	print_message(philosopher, "is thinking");
	pthread_mutex_lock(fork);
	print_message(philosopher, "has taken a fork");
}

static void	handle_eat(t_philosopher *philosopher)
{
	print_message(philosopher, "is eating");
	pthread_mutex_lock(&philosopher->last_meal_time_mutex);
	gettimeofday(&philosopher->last_meal, NULL);
	pthread_mutex_unlock(&philosopher->last_meal_time_mutex);
	philosopher_wait(philosopher, philosopher->philo->time_to_eat);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	philosopher->number_of_meals++;
	if (philosopher->philo->number_of_meals != -1
		&& philosopher->number_of_meals >= philosopher->philo->number_of_meals)
	{
		pthread_mutex_lock(&philosopher->philo->is_running_mutex);
		philosopher->philo->is_running = false;
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
	}
}

static void	philosopher_eat(t_philosopher *philosopher)
{
	if (!philosopher->left_fork || !philosopher->right_fork)
	{
		print_message(philosopher, "is thinking");
		philosopher_wait(philosopher, philosopher->philo->time_to_die);
		philosopher_wait(philosopher, philosopher->philo->time_to_die);
		return ;
	}
	if (philosopher->id % 2 == 0)
	{
		think_until_fork(philosopher, philosopher->left_fork);
		think_until_fork(philosopher, philosopher->right_fork);
	}
	else
	{
		think_until_fork(philosopher, philosopher->right_fork);
		think_until_fork(philosopher, philosopher->left_fork);
	}
	handle_eat(philosopher);
}

static void	philosopher_sleep(t_philosopher *philosopher)
{
	print_message(philosopher, "is sleeping");
	philosopher_wait(philosopher, philosopher->philo->time_to_sleep);
}

void	philosopher_routine(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	while (philosopher->philo->is_running)
	{
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		philosopher_eat(philosopher);
		philosopher_sleep(philosopher);
		pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	}
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
}
