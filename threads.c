/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:05:47 by pshandy           #+#    #+#             */
/*   Updated: 2022/05/28 17:05:49 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observe(void *tid)
{
	t_philo	*philo;

	philo = ((t_philo *)tid);
	while (philo->num_of_meals != philo->info->total)
	{
		if (current_time() - philo->last_meal_time > philo->info->time_to_die)
		{
			print(philo, DIE);
			*philo->is_dead = 1;
			return (NULL);
		}
	}
	return (NULL);
}

void	action(t_philo *philo, t_states action)
{
	int	timestamp;

	timestamp = current_time() - philo->start_time;
	print(philo, action);
	if (action == EAT)
	{
		philo->last_meal_time = current_time();
		philo->num_of_meals++;
		ft_usleep(philo->info->time_to_eat, philo);
	}
	else if (action == SLEEP)
		ft_usleep(philo->info->time_to_sleep, philo);
}

void	*simulation(void *tid)
{
	t_philo	*philo;

	philo = ((t_philo *)tid);
	if (!(philo->id % 2))
		ft_usleep(philo->info->time_to_eat, philo);
	while (philo->num_of_meals != philo->info->min_eat
		&& !(*philo->is_dead) && philo->info->total != 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		action(philo, FORK_TAKEN);
		action(philo, EAT);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		action(philo, SLEEP);
		action(philo, THINK);
	}
	return (NULL);
}
