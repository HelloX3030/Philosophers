/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:03 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/30 15:03:39 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	free_philo(t_philo *philo)
{
	int	i;

	i = 0;
	free(philo->philosophers);
	while (i < philo->number_philos)
		pthread_mutex_destroy(&philo->forks[i++].mutex);
	free(philo->forks);
	pthread_mutex_destroy(&philo->write_mutex);
	pthread_mutex_destroy(&philo->is_running_mutex);
}
