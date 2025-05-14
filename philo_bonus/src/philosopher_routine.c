/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:37 by hello_x           #+#    #+#             */
/*   Updated: 2025/05/14 14:22:12 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

static void	think_until_fork(t_philosopher *philosopher)
{
	print_message(philosopher, "is thinking");
	sem_wait(philosopher->philo->forks);
	print_message(philosopher, "has taken a fork");
}

static void	handle_eat(t_philosopher *philosopher)
{
	sem_wait(philosopher->data_mutex);
	gettimeofday(&philosopher->last_meal, NULL);
	sem_post(philosopher->data_mutex);
	print_message(philosopher, "is eating");
	philosopher_wait(philosopher, philosopher->philo->time_to_eat);
	sem_post(philosopher->philo->forks);
	sem_post(philosopher->philo->forks);
	sem_wait(philosopher->data_mutex);
	philosopher->number_of_meals++;
	sem_post(philosopher->data_mutex);
}

static void	philosopher_eat(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		custom_usleep(philosopher->philo->time_to_eat / 2);
	think_until_fork(philosopher);
	think_until_fork(philosopher);
	handle_eat(philosopher);
}

static void	philosopher_sleep(t_philosopher *philosopher)
{
	print_message(philosopher, "is sleeping");
	philosopher_wait(philosopher, philosopher->philo->time_to_sleep);
}

void	philosopher_routine(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		custom_usleep(philosopher->philo->time_to_eat / 2);
	while (1)
	{
		sem_wait(philosopher->philo->running_mutex);
		if (!philosopher->philo->running)
		{
			sem_post(philosopher->philo->running_mutex);
			break ;
		}
		sem_post(philosopher->philo->running_mutex);
		philosopher_eat(philosopher);
		philosopher_sleep(philosopher);
	}
}
