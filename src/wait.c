/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:33:03 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/05 11:04:24 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

bool	philosopher_finished(t_philosopher *philosopher)
{
	if (philosopher->philo->number_of_meals != -1
		&& philosopher->number_of_meals >= philosopher->philo->number_of_meals)
		return (true);
	if (philosopher->philo->is_running == false)
		return (true);
	return (false);
}

void	philosopher_wait(t_philosopher *philosopher, int time)
{
	int	time_waited;
	int	remaining_time;

	time_waited = 0;
	while (time_waited < time)
	{
		remaining_time = time - time_waited;
		if (remaining_time > 0 && remaining_time < WAIT_INTERVALL)
			usleep(remaining_time * 1000);
		else if (remaining_time > 0)
			usleep(WAIT_INTERVALL * 1000);
		time_waited += WAIT_INTERVALL;
		pthread_mutex_lock(&philosopher->philo->is_running_mutex);
		if (philosopher_finished(philosopher))
		{
			pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
	}
}

long long	get_elapsed_time(struct timeval *start_time)
{
	struct timeval	current_time;
	long long		elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - start_time->tv_sec) * 1000;
	elapsed_time += (current_time.tv_usec - start_time->tv_usec) / 1000;
	return (elapsed_time);
}

long long	get_time_diff(struct timeval *start_time, struct timeval *end_time)
{
	return ((end_time->tv_sec - start_time->tv_sec) * 1000 + (end_time->tv_usec
			- start_time->tv_usec) / 1000);
}
