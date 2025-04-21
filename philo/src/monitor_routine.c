/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:42:14 by nuno              #+#    #+#             */
/*   Updated: 2025/04/21 15:32:21 by nuno             ###   ########.fr       */
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
	long	time_elapsed;
	long	time_to_die;

	if (philo->full == true)
		return (false);
	time_elapsed = get_current_time(philo->table->start_time) - check_long(&philo->philo_mutex,
			&philo->time_last_eat);
	time_to_die = philo->table->time_to_die;
	if (time_elapsed > time_to_die)
		return (true);
	return (false);
}
