/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:37 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/29 14:06:35 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	philosopher_routine(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->philo->philo_data_mutex);
	if (philosopher->philo->is_running == false)
	{
		pthread_mutex_unlock(&philosopher->philo->philo_data_mutex);
		return ;
	}
	pthread_mutex_unlock(&philosopher->philo->philo_data_mutex);
	pthread_mutex_lock(&philosopher->philo->write_mutex);
	ft_putstr("Philosopher Routine started for Philosopher ");
	ft_putnbr_fd(philosopher->id, STDOUT_FILENO);
	ft_putstr("\n");
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	usleep(1000000);
}
