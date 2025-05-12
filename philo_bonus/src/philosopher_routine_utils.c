/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:59:51 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/12 18:39:21 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	print_message(t_philosopher *philosopher, char *message)
{
	sem_wait(philosopher->philo->running_mutex);
	if (philosopher->philo->running == false)
	{
		sem_post(philosopher->philo->running_mutex);
		return ;
	}
	sem_wait(philosopher->philo->write_mutex);
	printf("%lld %i %s\n", get_elapsed_time(&philosopher->philo->start_time),
		philosopher->id, message);
	sem_post(philosopher->philo->write_mutex);
	sem_post(philosopher->philo->running_mutex);
}
