/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello_x <hello_x@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:51:46 by lseeger           #+#    #+#             */
/*   Updated: 2025/05/19 13:47:17 by hello_x          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

static int get_int_len(int n)
{
	int len;

	if (n == 0)
		return (1);
	if (n < 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char *ft_itoa(int n)
{
	const int int_len = get_int_len(n);
	char *str;
	int i;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	str = malloc(sizeof(char) * (int_len + 1));
	if (str == NULL)
		return (NULL);
	i = int_len;
	if (n < 0)
	{
		n *= (-1);
		str[0] = '-';
	}
	else if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[--i] = '0' + (n % 10);
		n /= 10;
	}
	str[int_len] = 0;
	return (str);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	const int len1 = ft_strlen(s1);
	const int len2 = ft_strlen(s2);
	char *new_str;
	int i;
	int j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	while (++i < len1)
		new_str[i] = s1[i];
	j = -1;
	while (++j < len2)
		new_str[i + j] = s2[j];
	new_str[i + j] = 0;
	return (new_str);
}

char *ft_strdup(const char *s)
{
	char *new_str;
	const int s_len = ft_strlen(s);
	int i;

	new_str = malloc(s_len + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

size_t ft_strlen(const char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
