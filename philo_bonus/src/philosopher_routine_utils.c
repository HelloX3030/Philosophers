/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:59:51 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/07 15:52:51 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	print_message(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->philo->is_running_mutex);
	if (philosopher->philo->is_running == false)
	{
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		return ;
	}
	pthread_mutex_lock(&philosopher->philo->write_mutex);
	printf("%lld %i %s\n", get_elapsed_time(&philosopher->philo->start_time),
		philosopher->id, message);
	pthread_mutex_unlock(&philosopher->philo->write_mutex);
	pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
}
