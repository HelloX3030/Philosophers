/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:33:03 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/29 15:32:47 by lseeger          ###   ########.fr       */
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

	time_waited = 0;
	while (time_waited < time)
	{
		if (time_waited + WAIT_INTERVALL > time)
			usleep(time - time_waited);
		else
			usleep(WAIT_INTERVALL);
		time_waited += WAIT_INTERVALL;
		if (philosopher_finished(philosopher))
			break ;
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
