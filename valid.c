/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:05:11 by pshandy           #+#    #+#             */
/*   Updated: 2022/05/28 17:05:13 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_is_positive_number(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

static size_t	ft_strlen(const char *str)
{
	const char	*end;

	end = str;
	while (*end != '\0')
		end++;
	return (end - str);
}

static int	is_positive_int(char *str)
{
	size_t		i;

	if (*str == '0' || !ft_is_positive_number(str))
		return (0);
	if (ft_strlen(str) > 10)
		return (0);
	if (ft_strlen(str) < 10)
		return (1);
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] > "2147483648"[i])
			return (0);
		if (str[i] < "2147483648"[i])
			return (1);
		i++;
	}
	return (1);
}

int	ft_validate_input(char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
		if (!is_positive_int(argv[i++]))
			return (0);
	if (argv[i] && !is_positive_int(argv[i]))
		return (0);
	return (1);
}
