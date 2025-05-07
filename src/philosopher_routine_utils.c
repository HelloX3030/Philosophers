/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:59:51 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/06 16:53:14 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	take_fork(t_philosopher *philosopher, t_fork *fork)
{
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
	ft_putstr(" has taken a fork\n");
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
	fork->is_taken = true;
}

void	think_before_take_fork(t_philosopher *philosopher)
{
	long long	elapsed_time;

	pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	if (philosopher_finished(philosopher))
	{
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		return ;
	}
	pthread_mutex_lock(&philosopher->philo->write_mutex);
	elapsed_time = get_elapsed_time(&philosopher->philo->start_time);
	ft_putnbr_long_long_fd(elapsed_time, 1);
	ft_putstr(" ");
	ft_putnbr_fd(philosopher->id, 1);
	ft_putstr(" is thinking\n");
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
}

void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_taken = false;
	pthread_mutex_unlock(&fork->mutex);
}
