/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/03 14:13:32 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start(t_table *table)
{
	long	i;

	i = -1;
	if (table->nr_meals_limit == 0)
		return ; // back to the main to clean everything
	else if (table->num_of_philos == 1)
	{
		pthread_create(&table->philosophers[0].philo_thread, NULL, solo_routine, &table->philosophers[0]);
	}
	else
	{	
		while (++i < table->num_of_philos)
			pthread_create(&table->philosophers[i].philo_thread, NULL, routine, &table->philosophers[i]);
	}	
	//monitor thread
	pthread_create(&table->monitor_thread, NULL, monitor_routine, table);
	change_bool(table->start_time = get_time(MILISECONDS)); // make sure its change_bool
	pthread_join(table->monitor_thread, NULL);
	pthread_mutex_lock(&table->table_mutex);
	table->philos_are_ready = true;
	table->running = true;
	pthread_mutex_unlock(&table->table_mutex);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philosophers[i].philo_thread, NULL);
}
