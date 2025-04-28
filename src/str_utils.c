/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseeger <lseeger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:37:39 by lseeger           #+#    #+#             */
/*   Updated: 2025/04/25 14:37:51 by lseeger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void ft_putstr(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write(STDOUT_FILENO, str, len);
}

void ft_putstr_err(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write(STDERR_FILENO, str, len);
}
