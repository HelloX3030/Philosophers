/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:37 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/30 15:14:43 by lseeger          ###   ########.fr       */
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
	pthread_mutex_lock(&philosopher->philo->write_mutex);
	ft_putnbr_long_long_fd(get_elapsed_time(&philosopher->philo->start_time),
		1);
	ft_putstr(" ");
	ft_putnbr_fd(philosopher->id, 1);
	ft_putstr(" is eating\n");
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
	philosopher_wait(philosopher, philosopher->philo->time_to_eat);
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
	while (!philosopher_finished(philosopher))
	{
		philosopher_eat(philosopher);
		philosopher_sleep(philosopher);
	}
}
