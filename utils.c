/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:06:07 by pshandy           #+#    #+#             */
/*   Updated: 2022/05/28 17:06:08 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, t_states action)
{
	long	timestamp;

	pthread_mutex_lock(philo->print);
	timestamp = current_time() - philo->start_time;
	if (*philo->is_dead
		|| philo->num_of_meals == philo->info->min_eat)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	else if (action == FORK_TAKEN)
	{
		printf("%ld, philo %d has taken a fork\n", timestamp, philo->id);
		printf("%ld, philo %d has taken a fork\n", timestamp, philo->id);
	}
	else if (action == EAT)
		printf("%ld, philo %d is eating\n", timestamp, philo->id);
	else if (action == SLEEP)
		printf("%ld, philo %d is sleeping\n", timestamp, philo->id);
	else if (action == THINK)
		printf("%ld, philo %d is thinking\n", timestamp, philo->id);
	else if (action == DIE)
		printf("%ld, philo %d has died\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->print);
}

int	free_mem(t_philo *philo, pthread_mutex_t *fork)
{
	free(fork);
	free(philo);
	return (0);
}

int	ft_print_error(char *str)
{
	printf("Error: %s", str);
	return (-1);
}

int	ft_atoi(char *str)
{
	int	i;

	i = 0;
	while (*str >= '0' && *str <= '9')
		i = i * 10 + (*str++ - '0');
	return (i);
}
