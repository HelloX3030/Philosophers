/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello_x <hello_x@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:38:46 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/19 15:30:29 by hello_x          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

static void cleanup_semaphores(void)
{
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_RUNNING);
	sem_unlink(SEM_FORKS);
}

int main(int argc, char **argv)
{
	int i;
	t_philo philo;

	cleanup_semaphores();
	if (init_philo(&philo, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philosophers(&philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_join(philo.monitoring_thread, NULL);
	i = 0;
	while (i < philo.number_philos)
		pthread_join(philo.philosophers[i++].thread, NULL);
	return (free_philo(&philo), EXIT_SUCCESS);
}
