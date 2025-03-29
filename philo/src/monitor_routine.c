/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:42:14 by nuno              #+#    #+#             */
/*   Updated: 2025/03/29 12:01:53 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
			if (check_bool(&table->philosophers[i].philo_mutex, &table->philosophers[i].dead) == true)
			{
				change_bool(&table->table_mutex, &table->running, false);
				print_mutex(&table->philosophers[i], DEAD);
				return (NULL);
			}
			if (((long)get_time(MILISECONDS) - table->philosophers[i].time_last_eat) >= table->time_to_die)
			{
				change_bool(&table->philosophers[i].philo_mutex, &table->philosophers[i].dead, true);
				print_mutex(&table->philosophers[i], DEAD);
				change_bool(&table->table_mutex, &table->running, false);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}