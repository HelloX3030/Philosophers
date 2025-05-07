/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:33:03 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/07 16:32:29 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	philosopher_wait(t_philosopher *philosopher, int time_in_ms)
{
	long long	time;
	long long	time_waited;
	long long	remaining_time;

	time = time_in_ms * 1000;
	time_waited = 0;
	while (time_waited < time)
	{
		remaining_time = time - time_waited;
		if (remaining_time > 0 && remaining_time < WAIT_PHILOSOPHER)
			custom_usleep(remaining_time);
		else if (remaining_time > 0)
			custom_usleep(WAIT_PHILOSOPHER);
		time_waited += WAIT_PHILOSOPHER;
		pthread_mutex_lock(&philosopher->philo->is_running_mutex);
		if (philosopher->philo->is_running == false)
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

void	custom_usleep(long long time)
{
	struct timeval	start_time;
	struct timeval	current_time;

	gettimeofday(&start_time, NULL);
	while (get_time_diff_micro(&start_time, &current_time) < time)
	{
		gettimeofday(&current_time, NULL);
		usleep(WAIT_USLEEP);
	}
}

long long	get_time_diff_ms(struct timeval *start_time,
		struct timeval *end_time)
{
	return ((end_time->tv_sec - start_time->tv_sec) * 1000 + (end_time->tv_usec
			- start_time->tv_usec) / 1000);
}

long long	get_time_diff_micro(struct timeval *start_time,
		struct timeval *end_time)
{
	return ((end_time->tv_sec - start_time->tv_sec) * 1000000
		+ (end_time->tv_usec - start_time->tv_usec));
}
