/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:59 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/07 16:32:11 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	handle_death(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->philosophers[i].last_meal_time_mutex);
	pthread_mutex_lock(&philo->is_running_mutex);
	philo->is_running = false;
	pthread_mutex_lock(&philo->write_mutex);
	printf("%lld %i died\n", get_elapsed_time(&philo->start_time),
		philo->philosophers[i].id);
	pthread_mutex_unlock(&philo->write_mutex);
	pthread_mutex_unlock(&philo->is_running_mutex);
}

void	monitoring(t_philo *philo)
{
	struct timeval	current_time;
	int				i;

	pthread_mutex_lock(&philo->is_running_mutex);
	while (philo->is_running == true)
	{
		pthread_mutex_unlock(&philo->is_running_mutex);
		custom_usleep(WAIT_MONITORING);
		gettimeofday(&current_time, NULL);
		i = 0;
		while (i < philo->number_philos)
		{
			pthread_mutex_lock(&philo->philosophers[i].last_meal_time_mutex);
			if (get_time_diff_ms(&philo->philosophers[i].last_meal,
					&current_time) > philo->time_to_die)
				return (handle_death(philo, i));
			pthread_mutex_unlock(&philo->philosophers[i].last_meal_time_mutex);
			i++;
		}
	}
	pthread_mutex_unlock(&philo->is_running_mutex);
}
