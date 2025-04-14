/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/14 10:02:08 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start(t_table *table)
{
	long	i;

	i = -1;
	if (table->nr_meals_limit == 0)
		return ;
	else if (table->num_of_philos == 1)
		pthread_create(&table->philosophers[0].philo_thread, NULL, solo_routine,
			&table->philosophers[0]);
	else
	{
		while (++i < table->num_of_philos)
			pthread_create(&table->philosophers[i].philo_thread, NULL, routine,
				&table->philosophers[i]);
	}
	table->start_time = get_time(MILISECONDS);
	change_bool(&table->table_mutex, &table->running, true);
	change_bool(&table->table_mutex, &table->philos_are_ready, true);
	pthread_create(&table->monitor_thread, NULL, monitor_routine, table);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philosophers[i].philo_thread, NULL);
	change_bool(&table->table_mutex, &table->running, false);
	pthread_join(table->monitor_thread, NULL);
}
