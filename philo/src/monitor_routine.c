/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:42:14 by nuno              #+#    #+#             */
/*   Updated: 2025/04/18 23:10:19 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	philo_died(t_philo *philo);
static bool	did_all_eat(t_table *table);

void	*monitor_routine(void *data)
{
	t_table	*table;
	long	i;

	table = (t_table *)data;
	while (check_bool(&table->table_mutex, &table->running) == true)
	{
		i = -1;
		while (++i < table->num_of_philos)
		{
			if (check_bool(&table->table_mutex, &table->running) == false)
				break ;
			if (philo_died(&table->philosophers[i]) == true)
			{
				print_mutex(&table->philosophers[i], DEAD);
				change_bool(&table->table_mutex, &table->running, false);
				break ;
			}
		}
		if (did_all_eat(table) == true)
			return (NULL);
	}
	return (NULL);
}

static bool	did_all_eat(t_table *table)
{
	int		finished;
	int		i;

	i = -1;
	finished = 0;
	if (table->nr_meals_limit == -1)
		return (false);
	while (++i < table->num_of_philos)
	{
		if (check_bool(&table->philosophers[i].philo_mutex, &table->philosophers[i].full) == true)
			finished++;
	}
	if (finished == table->num_of_philos)
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

	if (check_bool(&philo->philo_mutex, &philo->full) == true)
		return (false);
	time_elapsed = get_current_time(philo->table->start_time) - check_long(&philo->philo_mutex,
			&philo->time_last_eat);
	time_to_die = philo->table->time_to_die;
	if (time_elapsed > time_to_die)
		return (true);
	return (false);
}
