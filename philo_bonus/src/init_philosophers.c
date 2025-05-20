/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:50:14 by hello_x           #+#    #+#             */
/*   Updated: 2025/05/20 13:39:12 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

static int	cleanup_philos(t_philo *philo, int i)
{
	while (i > 0)
	{
		i--;
		sem_unlink(philo->philosophers[i].data_mutex_name);
		free(philo->philosophers[i].data_mutex_name);
	}
	return (EXIT_FAILURE);
}

static int	create_philo_mutex(t_philo *philo, int i)
{
	char	*tmp;

	tmp = ft_itoa(i + 1);
	if (!tmp)
		return (cleanup_philos(philo, i), EXIT_FAILURE);
	philo->philosophers[i].data_mutex_name = ft_strjoin(SEM_PHILOSOPHER, tmp);
	free(tmp);
	if (!philo->philosophers[i].data_mutex_name)
		return (free(philo->philosophers[i].data_mutex_name),
			cleanup_philos(philo, i), EXIT_FAILURE);
	tmp = philo->philosophers[i].data_mutex_name;
	sem_unlink(tmp);
	philo->philosophers[i].data_mutex = sem_open(tmp, O_CREAT | O_EXCL, 0644,
			1);
	if (philo->philosophers[i].data_mutex == SEM_FAILED)
	{
		free(philo->philosophers[i].data_mutex_name);
		return (cleanup_philos(philo, i), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
		if (create_philo_mutex(philo, i) != EXIT_SUCCESS)
			return (free(philo->philosophers), EXIT_FAILURE);
		philo->philosophers[i].philo = philo;
		philo->philosophers[i].id = i + 1;
		philo->philosophers[i].number_of_meals = 0;
		philo->philosophers[i].last_meal = philo->start_time;
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
			sem_wait(philo->running_mutex);
			philo->running = false;
			sem_post(philo->running_mutex);
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

int	init_philosophers(t_philo *philo)
{
	sem_unlink(SEM_WRITE);
	philo->write_mutex = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1);
	if (philo->write_mutex == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink(SEM_RUNNING);
	philo->running_mutex = sem_open(SEM_RUNNING, O_CREAT | O_EXCL, 0644, 1);
	if (philo->running_mutex == SEM_FAILED)
		return (sem_unlink(SEM_WRITE), EXIT_FAILURE);
	sem_unlink(SEM_FORKS);
	philo->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644,
			philo->number_philos);
	if (philo->forks == SEM_FAILED)
		return (sem_unlink(SEM_WRITE), sem_unlink(SEM_RUNNING), EXIT_FAILURE);
	gettimeofday(&philo->start_time, NULL);
	if (init_philosopher(philo) != EXIT_SUCCESS)
		return (sem_unlink(SEM_FORKS), sem_unlink(SEM_WRITE),
			sem_unlink(SEM_RUNNING), EXIT_FAILURE);
	if (pthread_create(&philo->monitoring_thread, NULL, (void *)monitoring,
			philo) != 0)
		return (sem_unlink(SEM_WRITE), sem_unlink(SEM_RUNNING), EXIT_FAILURE);
	if (create_threads(philo) != EXIT_SUCCESS)
		return (free_philo(philo), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
