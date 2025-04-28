/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello_x <hello_x@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:03 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/28 12:09:41 by hello_x          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void free_philo(t_philo *philo)
{
	free(philo->philosophers);
	philo->philosophers = NULL;
	pthread_mutex_destroy(&philo->write_mutex);
}
