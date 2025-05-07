/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:37 by hello_x           #+#    #+#             */
/*   Updated: 2025/05/06 17:28:06 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	think_until_fork(t_philosopher *philosopher, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->is_taken)
	{
		pthread_mutex_unlock(&fork->mutex);
		think_before_take_fork(philosopher);
		while (1)
		{
			usleep(WAIT_INTERVALL);
			pthread_mutex_lock(&fork->mutex);
			if (!fork->is_taken)
				break ;
			pthread_mutex_unlock(&fork->mutex);
			pthread_mutex_lock(&philosopher->philo->is_running_mutex);
			if (philosopher_finished(philosopher))
			{
				pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
				return ;
			}
			pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		}
	}
	take_fork(philosopher, fork);
	pthread_mutex_unlock(&fork->mutex);
}

static void	handle_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo->write_mutex);
	ft_putnbr_long_long_fd(get_elapsed_time(&philosopher->philo->start_time),
		1);
	ft_putstr(" ");
	ft_putnbr_fd(philosopher->id, 1);
	ft_putstr(" is eating\n");
	pthread_mutex_lock(&philosopher->last_meal_time_mutex);
	gettimeofday(&philosopher->last_meal, NULL);
	pthread_mutex_unlock(&philosopher->last_meal_time_mutex);
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
	philosopher_wait(philosopher, philosopher->philo->time_to_eat);
	release_fork(philosopher->left_fork);
	release_fork(philosopher->right_fork);
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
	pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	if (philosopher_finished(philosopher))
	{
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		return ;
	}
	handle_eat(philosopher);
}

static void	philosopher_sleep(t_philosopher *philosopher)
{
	long long	elapsed_time;

	pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	if (philosopher_finished(philosopher))
	{
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		return ;
	}
	elapsed_time = get_elapsed_time(&philosopher->philo->start_time);
	pthread_mutex_lock(&philosopher->philo->write_mutex);
	ft_putnbr_long_long_fd(elapsed_time, 1);
	ft_putstr(" ");
	ft_putnbr_fd(philosopher->id, 1);
	ft_putstr(" is sleeping\n");
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
	philosopher_wait(philosopher, philosopher->philo->time_to_sleep);
}

void	philosopher_routine(t_philosopher *philosopher)
{
	if (philosopher->philo->number_philos == 1)
	{
		think_before_take_fork(philosopher);
		philosopher_wait(philosopher, philosopher->philo->time_to_die);
		philosopher_wait(philosopher, philosopher->philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	while (!philosopher_finished(philosopher))
	{
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		philosopher_eat(philosopher);
		philosopher_sleep(philosopher);
		pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	}
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
}
