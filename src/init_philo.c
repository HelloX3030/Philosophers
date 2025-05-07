/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:58:30 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/07 14:12:21 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	check_limits(t_philo *philo)
{
	if (philo->number_philos < 1 || philo->number_philos > 200)
	{
		printf("Error: number_of_philos must be between 0 and 200\n");
		return (EXIT_FAILURE);
	}
	if (philo->time_to_die < 60)
	{
		printf("Error: time_to_die must be >= 60\n");
		return (EXIT_FAILURE);
	}
	if (philo->time_to_eat < 60)
	{
		printf("Error: time_to_eat must be >= 60\n");
		return (EXIT_FAILURE);
	}
	if (philo->time_to_sleep < 60)
	{
		printf("Error: time_to_sleep must be >= 60\n");
		return (EXIT_FAILURE);
	}
	if (philo->number_of_meals != -1 && philo->number_of_meals < 0)
		return (printf("Error: number_of_meals must be >= 0\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_values(t_philo *philo, char **argv)
{
	if (!ft_aisi(argv[1]))
	{
		printf("Error: Invalid Input for number_of_philosophers\n");
		return (EXIT_FAILURE);
	}
	philo->number_philos = ft_atoi(argv[1]);
	if (!ft_aisi(argv[2]))
	{
		printf("Error: Invalid Input for time_to_die\n");
		return (EXIT_FAILURE);
	}
	philo->time_to_die = ft_atoi(argv[2]);
	if (!ft_aisi(argv[3]))
	{
		printf("Error: Invalid Input for time_to_eat\n");
		return (EXIT_FAILURE);
	}
	philo->time_to_eat = ft_atoi(argv[3]);
	if (!ft_aisi(argv[4]))
	{
		printf("Error: Invalid Input for time_to_sleep\n");
		return (EXIT_FAILURE);
	}
	philo->time_to_sleep = ft_atoi(argv[4]);
	return (EXIT_SUCCESS);
}

int	init_philo(t_philo *philo, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("<number_of_philos> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> [number_of_meals]\n");
		return (EXIT_FAILURE);
	}
	philo->is_running = true;
	if (init_values(philo, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		if (!ft_aisi(argv[5]))
		{
			printf("Error: Invalid Input for number_of_meals\n");
			return (EXIT_FAILURE);
		}
		philo->number_of_meals = ft_atoi(argv[5]);
		if (philo->number_of_meals == -1)
			return (printf("Error: number_of_meals must be > 0\n"),
				EXIT_FAILURE);
	}
	else
		philo->number_of_meals = -1;
	return (check_limits(philo));
}
