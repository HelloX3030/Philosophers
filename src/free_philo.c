/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello_x <hello_x@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:09:03 by hello_x           #+#    #+#             */
/*   Updated: 2025/04/28 12:36:37 by hello_x          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void free_philo(t_philo *philo)
{
	free(philo->philosophers);
	pthread_mutex_destroy(&philo->write_mutex);
	pthread_mutex_destroy(&philo->philo_data_mutex);
}
