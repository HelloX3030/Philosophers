/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:03 by hello_x           #+#    #+#             */
/*   Updated: 2025/05/12 18:21:13 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	free_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_philos)
	{
		sem_unlink(philo->philosophers[i].data_mutex_name);
		free(philo->philosophers[i].data_mutex_name);
		i++;
	}
	free(philo->philosophers);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_RUNNING);
	sem_unlink(SEM_FORKS);
}
