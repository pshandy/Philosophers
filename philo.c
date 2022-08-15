/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:05:37 by pshandy           #+#    #+#             */
/*   Updated: 2022/05/28 17:05:38 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo(t_philo *philo, int num_of_philos, pthread_t *waiter)
{
	int			i;
	pthread_t	*philo_thread;

	i = 0;
	philo_thread = malloc(sizeof(pthread_t) * num_of_philos);
	if (!philo_thread)
		return (0);
	while (i < num_of_philos)
	{
		if (pthread_create(
				&philo_thread[i], NULL, &simulation, (void *)(philo + i)))
			return (0);
		i++;
	}
	if (pthread_join(*waiter, NULL))
		return (0);
	while (i--)
		if (pthread_join(philo_thread[i], NULL))
			return (0);
	free(philo_thread);
	return (1);
}

int	create_threads(t_philo *philo, pthread_mutex_t	*fork)
{
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, &observe, (void *)philo))
		return (0);
	if (create_philo(philo, philo->info->total, &waiter))
		return (0);
	if (pthread_mutex_destroy(fork))
		return (0);
	if (pthread_mutex_destroy(philo->print))
		return (0);
	return (1);
}

int	start(t_info *info)
{
	int				is_dead;
	t_philo			*philos_array;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*fork_mutexes;

	is_dead = 0;
	pthread_mutex_init(&print_mutex, NULL);
	fork_mutexes = malloc(sizeof(pthread_mutex_t) * info->total);
	if (!fork_mutexes)
		return (0);
	philos_array = init_philo(fork_mutexes, &print_mutex, info, &is_dead);
	if (!philos_array)
		return (free_mem(NULL, fork_mutexes));
	if (create_threads(philos_array, fork_mutexes))
		return (free_mem(philos_array, fork_mutexes));
	free_mem(philos_array, fork_mutexes);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (ft_print_error(
				"Usage:"
				"./philo [number of philosophers]"
				" [time to die] [time to eat] [time to sleep]"
				" [number_of_times_each_philosopher must eat]\n"
			));
	if (!ft_validate_input(argv))
		return (ft_print_error("Wrong input!\n"));
	get_info(argv, &info);
	if (!start(&info))
		return (ft_print_error("Error while creating streams!\n"));
}
