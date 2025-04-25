/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:38:12 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/25 16:13:47 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Number Utils
int		ft_atoi(const char *str);
bool	ft_aisi(char *str);
void	ft_putnbr_fd(int n, int fd);
int		ft_isdigit(int c);

// Str Utils
void	ft_putstr(char *str);
void	ft_putstr_err(char *str);

// Philosopher Struct
typedef struct s_philo
{
	int	number_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
}		t_philo;

int		init_philosophers(t_philo *philo, int argc, char **argv);
void	print_philo(t_philo *philo);

#endif
