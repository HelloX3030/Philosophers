/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:38:46 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/25 16:17:37 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (init_philosophers(&philo, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// run philosophers
	print_philo(&philo);
	return (EXIT_SUCCESS);
}
