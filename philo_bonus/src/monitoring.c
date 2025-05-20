/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:59 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/20 13:39:09 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

static void	handle_death(t_philo *philo, int i)
{
	sem_wait(philo->running_mutex);
	philo->running = false;
	sem_wait(philo->write_mutex);
	printf("%lld %i died\n", get_elapsed_time(&philo->start_time),
		philo->philosophers[i].id);
	sem_post(philo->write_mutex);
	sem_post(philo->running_mutex);
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
		sem_wait(philo->philosophers[i].data_mutex);
		if (!check_full(&philo->philosophers[i]))
			all_eaten = false;
		if (check_death(&philo->philosophers[i]))
		{
			handle_death(philo, i);
			sem_post(philo->philosophers[i].data_mutex);
			return (true);
		}
		sem_post(philo->philosophers[i].data_mutex);
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
		sem_wait(philo->running_mutex);
		if (!philo->running)
		{
			sem_post(philo->running_mutex);
			return ;
		}
		sem_post(philo->running_mutex);
		if (check_philos(philo))
		{
			sem_wait(philo->running_mutex);
			philo->running = false;
			sem_post(philo->running_mutex);
			return ;
		}
	}
}
