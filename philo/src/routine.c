/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:29 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/22 23:56:20 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*solo_routine(t_philo *philo);
static void make_philos_wait(t_philo *philo);
static void	arroz_de_cabidela(t_philo *philo);

void	*routine(void *philoso)
{
	t_philo	*philo;

	philo = (t_philo *)philoso;
	increase_long(&philo->table->table_mutex, &philo->table->num_threads_running);

	// Wait until all threads are created and start signal is given
	while (!check_bool(&philo->table->table_mutex, &philo->table->philos_are_ready))
		usleep(100);

	// Now wait until the simulation officially starts
	while (!check_bool(&philo->table->table_mutex, &philo->table->running))
		usleep(100);
	if (philo->table->num_of_philos == 1)
		return (solo_routine(philo), NULL);
	make_philos_wait(philo);
	while (check_bool(&philo->table->table_mutex,
		&philo->table->running) == true)
	{
		arroz_de_cabidela(philo);
		print_mutex(philo, SLEEPING);
		if (philo->table->nr_meals_limit == philo->eat_count && philo->table->nr_meals_limit > 0)
		{
			philo->full = true;
			break ;
		}
		ft_usleep(philo->table->time_to_sleep);
		print_mutex(philo, THINKING);
	}
	decrease_long(&philo->table->table_mutex, &philo->table->num_threads_running);
	return (NULL);
}

static void	arroz_de_cabidela(t_philo *philo)
{
	// Lock forks in consistent order
	mutex_handle(&philo->left_fork->fork, LOCK);
	print_mutex(philo, FIRST_FORK);
	mutex_handle(&philo->right_fork->fork, LOCK);
	print_mutex(philo, SECOND_FORK);
	
	pthread_mutex_lock(&philo->philo_mutex);
	philo->time_last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	
	print_mutex(philo, EATING);
	ft_usleep(philo->table->time_to_eat);
	increase_long(&philo->table->table_mutex, &philo->eat_count);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}

static void	*solo_routine(t_philo *philo)
{
	print_mutex(philo, FIRST_FORK);
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == true)
		ft_usleep(100);
	return (NULL);
}

static void make_philos_wait(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(40);
}
