/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:59 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/06 17:10:13 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	handle_death(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->philosophers[i].last_meal_time_mutex);
	philo->is_running = false;
	pthread_mutex_lock(&philo->write_mutex);
	ft_putnbr_long_long_fd(get_elapsed_time(&philo->start_time), 1);
	ft_putstr(" ");
	ft_putnbr_fd(philo->philosophers[i].id, 1);
	ft_putstr(" died\n");
	pthread_mutex_unlock(&philo->write_mutex);
	pthread_mutex_unlock(&philo->is_running_mutex);
}

void	monitoring(t_philo *philo)
{
	struct timeval	current_time;
	int				i;

	while (true)
	{
		usleep(WAIT_INTERVALL);
		pthread_mutex_lock(&philo->is_running_mutex);
		if (philo->is_running == false)
		{
			pthread_mutex_unlock(&philo->is_running_mutex);
			return ;
		}
		gettimeofday(&current_time, NULL);
		i = 0;
		while (i < philo->number_philos)
		{
			pthread_mutex_lock(&philo->philosophers[i].last_meal_time_mutex);
			if (get_time_diff(&philo->philosophers[i].last_meal,
					&current_time) > philo->time_to_die)
				return (handle_death(philo, i));
			pthread_mutex_unlock(&philo->philosophers[i].last_meal_time_mutex);
			i++;
		}
		pthread_mutex_unlock(&philo->is_running_mutex);
	}
}
