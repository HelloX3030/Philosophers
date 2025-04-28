/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello_x <hello_x@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:50:14 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/28 12:08:38 by hello_x          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int init_philosophers(t_philo *philo)
{
	int i;

	philo->philosophers = malloc(sizeof(t_philosopher) * philo->number_philos);
	if (!philo->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i <= philo->number_philos)
	{
		philo->philosophers[i].philo = philo;
		philo->philosophers[i].id = i + 1;
		philo->philosophers[i].number_of_meals = 0;
		philo->philosophers[i].last_meal_time = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}
