/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:03 by hello_x           #+#    #+#             */
/*   Updated: 2025/05/20 13:38:26 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	free_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_philos)
		pthread_mutex_destroy(&philo->philosophers[i++].data_mutex);
	free(philo->philosophers);
	i = 0;
	while (i < philo->number_philos)
		pthread_mutex_destroy(&philo->forks[i++]);
	free(philo->forks);
	pthread_mutex_destroy(&philo->write_mutex);
	pthread_mutex_destroy(&philo->is_running_mutex);
}
