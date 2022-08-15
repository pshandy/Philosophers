/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:04:59 by pshandy           #+#    #+#             */
/*   Updated: 2022/05/28 17:05:01 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_info
{
	int	total;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_eat;
}		t_info;

typedef struct s_philo
{
	int				id;
	int				num_of_meals;
	long			start_time;
	long			last_meal_time;
	int				*is_dead;
	struct s_info	*info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
}	t_philo;

typedef enum e_states
{
	FORK_TAKEN,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_states;

int		ft_print_error(char *str);
int		ft_atoi(char *str);
void	print(t_philo *philo, t_states action);
int		free_mem(t_philo *philo, pthread_mutex_t *fork);
void	get_info(char *argv[], t_info *info);
t_philo	*init_philo(pthread_mutex_t *fork, pthread_mutex_t *print,
			t_info *info, int *is_dead);
int		ft_validate_input(char **argv);
void	*observe(void *tid);
void	action(t_philo *philo, t_states action);
void	*simulation(void *tid);
long	current_time(void);
void	ft_usleep(long millisec, t_philo *philo);

#endif
