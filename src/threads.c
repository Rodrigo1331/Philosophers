/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcruz-an <rcruz-an@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:01:57 by rcruz-an          #+#    #+#             */
/*   Updated: 2024/06/28 17:52:39 by rcruz-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* static void	init_time(t_philo *philos)
{
	int			i;
	long int	start;

	i = 0;
	start = get_current_time();
	while (i < philos->num_of_philos)
	{
		philos[i].start_time = start;
		philos[i].last_meal = start;
		//program->philos[i].philo_input = input;
		i++;
	}
} */

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->num_of_philos == 1)
	{
		print_message("has taken a fork", philo, philo->id);
		ft_usleep(philo->time_to_die);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (!dead_loop(philo))
	{
		if (philo->id % 2 == 0)
			eat_odd(philo);
		else
			eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	/* init_time(program->philos); */
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_create(&program->philos[i].thread, NULL, &philo_routine,
			&program->philos[i]);
		i++;
	}
	pthread_create(&observer, NULL, &monitor, program->philos);
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", program, forks);
		i++;
	}
	return (0);
}

/* int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destory_all("Thread creation error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destory_all("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", program, forks);
		i++;
	}
	return (0);
} */
