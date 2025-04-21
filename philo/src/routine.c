/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:29 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/21 14:56:31 by nuno             ###   ########.fr       */
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
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == false)
		usleep(1);
	increase_long(&philo->table->table_mutex, &philo->table->num_threads_running);
	if (philo->table->num_of_philos == 1)
		return (solo_routine(philo), NULL);
	make_philos_wait(philo);
	while (check_bool(&philo->table->table_mutex,
		&philo->table->running) == true)
	{
	/* 	while (check_if_i_can_eat(philo) == false)
			ft_usleep(1); */
		arroz_de_cabidela(philo);
		print_mutex(philo, SLEEPING);
		if (philo->table->nr_meals_limit == philo->eat_count)
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
	mutex_handle(&philo->left_fork->fork, LOCK);
	print_mutex(philo, FIRST_FORK);
	mutex_handle(&philo->right_fork->fork, LOCK);
	print_mutex(philo, SECOND_FORK);
	print_mutex(philo, EATING);
	change_long(&philo->philo_mutex, &philo->time_last_eat, get_current_time(philo->table->start_time));
	ft_usleep(philo->table->time_to_eat);
	increase_long(&philo->philo_mutex , &philo->eat_count);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}

static void	*solo_routine(t_philo *philo)
{
	print_mutex(philo, FIRST_FORK);
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == true)
		usleep(100);
	return (NULL);
}

static void make_philos_wait(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(1);
}
