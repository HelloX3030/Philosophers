/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello_x <hello_x@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:40:32 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/28 12:40:41 by hello_x          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void print_philosopher(t_philosopher *philosopher)
{
	ft_putstr("Philosopher ");
	ft_putnbr_fd(philosopher->id, STDOUT_FILENO);
	ft_putstr(":\n");
	ft_putstr("\tNumber of Meals: ");
	ft_putnbr_fd(philosopher->number_of_meals, STDOUT_FILENO);
	ft_putstr("\n\tLast Meal Time: ");
	ft_putnbr_fd(philosopher->last_meal_time, STDOUT_FILENO);
	ft_putstr("\n");
}

static void print_philosophers(t_philo *philo)
{
	int i = 0; 
	while (i < philo->number_philos)
	{
		print_philosopher(philo->philosophers + i);
		i++;
	}
}

void	print_philo(t_philo *philo)
{
	ft_putstr("Philosophers: ");
	ft_putnbr_fd(philo->number_philos, STDOUT_FILENO);
	ft_putstr("\nTime to Die: ");
	ft_putnbr_fd(philo->time_to_die, STDOUT_FILENO);
	ft_putstr("\nTime to Eat: ");
	ft_putnbr_fd(philo->time_to_eat, STDOUT_FILENO);
	ft_putstr("\nTime to Sleep: ");
	ft_putnbr_fd(philo->time_to_sleep, STDOUT_FILENO);
	if (philo->number_of_meals != -1)
	{
		ft_putstr("\nNumber of Meals: ");
		ft_putnbr_fd(philo->number_of_meals, STDOUT_FILENO);
	}
	ft_putstr("\n========================\n");
	print_philosophers(philo);
}
