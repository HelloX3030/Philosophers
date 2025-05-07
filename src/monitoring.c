/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:59 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/07 18:33:49 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	handle_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->is_running_mutex);
	philo->is_running = false;
	pthread_mutex_lock(&philo->write_mutex);
	printf("%lld %i died\n", get_elapsed_time(&philo->start_time),
		philo->philosophers[i].id);
	pthread_mutex_unlock(&philo->write_mutex);
	pthread_mutex_unlock(&philo->is_running_mutex);
}

static bool	check_death(t_philosopher *philosopher)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (get_time_diff_ms(&philosopher->last_meal,
			&current_time) > philosopher->philo->time_to_die)
		return (true);
	return (false);
}

static bool	check_full(t_philosopher *philosopher)
{
	if (philosopher->philo->number_of_meals != -1
		&& philosopher->number_of_meals >= philosopher->philo->number_of_meals)
		return (true);
	return (false);
}

static bool	check_philos(t_philo *philo)
{
	int		i;
	bool	all_eaten;

	all_eaten = true;
	i = 0;
	while (i < philo->number_philos)
	{
		pthread_mutex_lock(&philo->philosophers[i].last_meal_time_mutex);
		if (!check_full(&philo->philosophers[i]))
			all_eaten = false;
		if (check_death(&philo->philosophers[i]))
		{
			handle_death(philo, i);
			pthread_mutex_unlock(&philo->philosophers[i].last_meal_time_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philo->philosophers[i].last_meal_time_mutex);
		i++;
	}
	if (all_eaten)
		return (true);
	else
		return (false);
}

void	monitoring(t_philo *philo)
{
	while (1)
	{
		custom_usleep(WAIT_MONITORING);
		pthread_mutex_lock(&philo->is_running_mutex);
		if (!philo->is_running)
		{
			pthread_mutex_unlock(&philo->is_running_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->is_running_mutex);
		if (check_philos(philo))
			return ;
	}
}
