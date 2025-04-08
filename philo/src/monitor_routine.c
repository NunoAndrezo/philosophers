/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:42:14 by nuno              #+#    #+#             */
/*   Updated: 2025/04/08 11:54:14 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	philo_died(t_philo *philo);
static bool	are_all_threads_running(t_mutex *mutex, long *nr_of_threads, long nr_of_philos);

void	*monitor_routine(void *data)
{
	t_table	*table;
	long	i;

	table = (t_table *)data;
	while (are_all_threads_running(&table->table_mutex, &table->num_threads_running, table->num_of_philos) == false)
		usleep(10);
	while (check_bool(&table->table_mutex, &table->running))
	{
		i = -1;
		while (++i < table->num_of_philos && check_bool(&table->table_mutex, &table->running))
		{
			if (philo_died(table->philosophers + i))
			{
				change_bool(&table->table_mutex, &table->running, false);
				print_mutex(&table->philosophers[i], DEAD);
				break ;
			}
		}
	}
	return (NULL);
}

static bool	philo_died(t_philo *philo)
{
	long	time_elapsed;
	long	time_to_die;

	if (check_bool(&philo->philo_mutex, &philo->full) == true)
		return (false);
	time_elapsed = get_time(MILISECONDS) - check_long(&philo->philo_mutex, &philo->time_last_eat);
	time_to_die = philo->table->time_to_die / 1000;
	if (time_elapsed >= time_to_die)
		return (true);
	return (false);
}

static bool	are_all_threads_running(t_mutex *mutex, long *nr_of_threads, long nr_of_philos)
{
	bool	ret;

	ret = false;
	mutex_handle(mutex, LOCK);
	if (*nr_of_threads == nr_of_philos)
		ret = true;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}
