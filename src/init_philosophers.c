/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:50:14 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/29 14:59:29 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	init_philosopher(t_philo *philo)
{
	int	i;

	philo->philosophers = malloc(sizeof(t_philosopher) * philo->number_philos);
	if (!philo->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i < philo->number_philos)
	{
		philo->philosophers[i].philo = philo;
		philo->philosophers[i].id = i + 1;
		philo->philosophers[i].number_of_meals = 0;
		philo->philosophers[i].last_meal_time = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_philos)
	{
		if (pthread_create(&philo->philosophers[i].thread, NULL,
				(void *)philosopher_routine, philo->philosophers + i) != 0)
		{
			pthread_mutex_lock(&philo->philo_data_mutex);
			philo->is_running = false;
			pthread_mutex_unlock(&philo->philo_data_mutex);
			while (i >= 0)
			{
				pthread_join(philo->philosophers[i - 1].thread, NULL);
				i--;
			}
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_philosophers(t_philo *philo)
{
	if (pthread_mutex_init(&philo->write_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&philo->philo_data_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	if (init_philosopher(philo) != EXIT_SUCCESS)
	{
		pthread_mutex_destroy(&philo->write_mutex);
		pthread_mutex_destroy(&philo->philo_data_mutex);
		return (EXIT_FAILURE);
	}
	gettimeofday(&philo->start_time, NULL);
	if (create_threads(philo) != EXIT_SUCCESS)
		return (free_philo(philo), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
