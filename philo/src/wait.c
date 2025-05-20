/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:33:03 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/20 13:38:43 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	philosopher_wait(t_philosopher *philosopher, int time_in_ms)
{
	struct timeval	current_time;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&current_time, NULL);
	while (get_time_diff_ms(&start_time, &current_time) < time_in_ms)
	{
		custom_usleep(WAIT_PHILOSOPHER);
		pthread_mutex_lock(&philosopher->philo->is_running_mutex);
		if (!philosopher->philo->is_running)
		{
			pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher->philo->is_running_mutex);
		gettimeofday(&current_time, NULL);
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
	long long	sec_diff;
	long long	usec_diff;

	sec_diff = end_time->tv_sec - start_time->tv_sec;
	usec_diff = end_time->tv_usec - start_time->tv_usec;
	return (sec_diff * 1000 + usec_diff / 1000);
}

long long	get_time_diff_micro(struct timeval *start_time,
		struct timeval *end_time)
{
	return ((end_time->tv_sec - start_time->tv_sec) * 1000000
		+ (end_time->tv_usec - start_time->tv_usec));
}
