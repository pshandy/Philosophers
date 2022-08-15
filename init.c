/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:05:22 by pshandy           #+#    #+#             */
/*   Updated: 2022/05/28 17:05:23 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_info(char *argv[], t_info *info)
{
	info->total = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->min_eat = ft_atoi(argv[5]);
	else
		info->min_eat = -1;
}

t_philo	*init_philo(pthread_mutex_t *fork, pthread_mutex_t *print,
			t_info *info, int *is_dead)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * info->total);
	if (!philo)
		return (NULL);
	while (i < info->total)
	{
		philo[i].id = i + 1;
		philo[i].num_of_meals = 0;
		philo[i].start_time = current_time();
		philo[i].last_meal_time = current_time();
		philo[i].is_dead = is_dead;
		philo[i].info = info;
		philo[i].left_fork = fork + i;
		philo[i].right_fork = fork + ((i + 1) % info->total);
		philo[i].print = print;
		pthread_mutex_init(fork + i, NULL);
		i++;
	}
	return (philo);
}
