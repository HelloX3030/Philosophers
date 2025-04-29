/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:05:29 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/29 15:05:24 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static bool	check_limits(long long result, bool is_negative)
{
	long long	check;

	if (is_negative)
	{
		check = result * -1;
		if (check < INT_MIN)
			return (false);
	}
	else
	{
		check = result;
		if (check > INT_MAX)
			return (false);
	}
	return (true);
}

bool	ft_aisi(char *str)
{
	long long	result;
	bool		is_negative;

	result = 0;
	is_negative = false;
	if (!str)
		return (false);
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		is_negative = true;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		result = result * 10 + *str - '0';
		if (!check_limits(result, is_negative))
			return (false);
		str++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num * sign);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
