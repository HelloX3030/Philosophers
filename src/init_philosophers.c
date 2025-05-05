/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:50:14 by hello_x           #+#    #+#             */
/*   Updated: 2025/05/05 11:34:42 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	clear_philosophers(t_philo *philo, int i)
{
	while (i > 0)
	{
		pthread_mutex_destroy(&philo->philosophers[i - 1].last_meal_time_mutex);
		i--;
	}
}

static int	init_philosopher(t_philo *philo)
{
	int	i;

	philo->philosophers = malloc(sizeof(t_philosopher) * philo->number_philos);
	if (!philo->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i < philo->number_philos)
	{
		if (pthread_mutex_init(&philo->philosophers[i].last_meal_time_mutex,
				NULL) != 0)
			return (clear_philosophers(philo, i), EXIT_FAILURE);
		philo->philosophers[i].philo = philo;
		philo->philosophers[i].id = i + 1;
		philo->philosophers[i].number_of_meals = 0;
		philo->philosophers[i].last_meal_time = philo->start_time;
		philo->philosophers[i].left_fork = &philo->forks[i];
		if (i == philo->number_philos - 1)
			philo->philosophers[i].right_fork = &philo->forks[0];
		else
			philo->philosophers[i].right_fork = &philo->forks[i + 1];
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
			pthread_mutex_lock(&philo->is_running_mutex);
			philo->is_running = false;
			pthread_mutex_unlock(&philo->is_running_mutex);
			while (i > 0)
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

static int	init_forks(t_philo *philo)
{
	int	i;

	philo->forks = malloc(sizeof(t_fork) * philo->number_philos);
	if (!philo->forks)
		return (EXIT_FAILURE);
	i = 0;
	while (i < philo->number_philos)
	{
		if (pthread_mutex_init(&philo->forks[i].mutex, NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&philo->forks[i - 1].mutex);
				i--;
			}
			free(philo->forks);
			return (EXIT_FAILURE);
		}
		philo->forks[i].is_taken = false;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_philosophers(t_philo *philo)
{
	if (pthread_mutex_init(&philo->write_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&philo->is_running_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&philo->write_mutex), EXIT_FAILURE);
	if (init_forks(philo) != EXIT_SUCCESS)
		return (pthread_mutex_destroy(&philo->write_mutex),
			pthread_mutex_destroy(&philo->is_running_mutex), EXIT_FAILURE);
	gettimeofday(&philo->start_time, NULL);
	if (init_philosopher(philo) != EXIT_SUCCESS)
	{
		pthread_mutex_destroy(&philo->write_mutex);
		pthread_mutex_destroy(&philo->is_running_mutex);
		return (EXIT_FAILURE);
	}
	if (pthread_create(&philo->monitoring_thread, NULL, (void *)monitoring,
			philo) != 0)
	{
		pthread_mutex_destroy(&philo->write_mutex);
		pthread_mutex_destroy(&philo->is_running_mutex);
		return (EXIT_FAILURE);
	}
	if (create_threads(philo) != EXIT_SUCCESS)
		return (free_philo(philo), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
