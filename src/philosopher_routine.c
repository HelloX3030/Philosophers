/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:37 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/29 15:37:00 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	philosopher_eat(t_philosopher *philosopher)
{
	if (philosopher_finished(philosopher))
		return ;
}

static void	philosopher_sleep(t_philosopher *philosopher)
{
	long long	elapsed_time;
	int			time_to_sleep;

	pthread_mutex_lock(&philosopher->philo->philo_data_mutex);
	if (philosopher_finished(philosopher))
		return ;
	elapsed_time = get_elapsed_time(&philosopher->philo->start_time);
	time_to_sleep = philosopher->philo->time_to_sleep;
	pthread_mutex_lock(&philosopher->philo->write_mutex);
	ft_putnbr_long_long_fd(elapsed_time, 1);
	ft_putstr(" ");
	ft_putnbr_fd(philosopher->id, 1);
	ft_putstr(" is sleeping\n");
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	pthread_mutex_unlock(&philosopher->philo->philo_data_mutex);
	philosopher_wait(philosopher, time_to_sleep);
}

static void	philosopher_think(t_philosopher *philosopher)
{
	if (philosopher_finished(philosopher))
		return ;
}

void	philosopher_routine(t_philosopher *philosopher)
{
	while (!philosopher_finished(philosopher))
	{
		philosopher_eat(philosopher);
		philosopher_sleep(philosopher);
		philosopher_think(philosopher);
	}
}
