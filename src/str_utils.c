/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:37:39 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/29 15:05:09 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(STDOUT_FILENO, str, len);
}

void	ft_putstr_err(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(STDERR_FILENO, str, len);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n <= 9)
		write(fd, &"0123456789"[n], 1);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		write(fd, &"0123456789"[n % 10], 1);
	}
}

void	ft_putnbr_long_long_fd(long long n, int fd)
{
	if (n == LLONG_MIN)
	{
		write(fd, "-9223372036854775808", 20);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n <= 9)
		write(fd, &"0123456789"[n], 1);
	else
	{
		ft_putnbr_long_long_fd(n / 10, fd);
		write(fd, &"0123456789"[n % 10], 1);
	}
}
