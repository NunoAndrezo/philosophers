/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:42:14 by nuno              #+#    #+#             */
/*   Updated: 2025/04/22 23:51:43 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	philo_died(t_philo *philo);
static bool	did_all_leave(t_table *table);

void	*monitor_routine(void *data)
{
	t_table	*table;
	long	i;

	table = (t_table *)data;
	while (check_long(&table->table_mutex, &table->num_threads_running) != table->num_of_philos)
		usleep(1);
	while (check_bool(&table->table_mutex, &table->running) == true)
	{
		i = -1;
		while (++i < table->num_of_philos)
		{
			if (philo_died(&table->philosophers[i]) == true)
			{
				print_mutex(&table->philosophers[i], DEAD);
				change_bool(&table->table_mutex, &table->running, false);
				break ;
			}
		}
		if (did_all_leave(table) == true)
			return (NULL);
	}
	return (NULL);
}

static bool	did_all_leave(t_table *table)
{
	if (check_long(&table->table_mutex, &table->num_threads_running) == 0)
	{
		change_bool(&table->table_mutex, &table->running, false);
		return (true);
	}
	return (false);
}

static bool	philo_died(t_philo *philo)
{
/* 	long	time_elapsed;
	long	time_to_die;
	long	t_last_eat;

	if (philo->full == true)
		return (false);
	t_last_eat = check_long(&philo->table->table_mutex, &philo->time_last_eat);
	time_elapsed = get_current_time(philo->table->start_time) - t_last_eat;
	time_to_die = philo->table->time_to_die;
	if (time_elapsed > time_to_die + 5)
		return (true);
	return (false); */
	long now;
	long elapsed;

	if (philo->full == true)
		return (false);
	pthread_mutex_lock(&philo->philo_mutex);
	now = get_time();
	elapsed = now - philo->time_last_eat;
	pthread_mutex_unlock(&philo->philo_mutex);

	if (elapsed > philo->table->time_to_die + 5)
	{
		print_mutex(philo, DEAD);
		change_bool(&philo->table->table_mutex, &philo->table->running, false);
		return (true);
	}
	return (false);
}
