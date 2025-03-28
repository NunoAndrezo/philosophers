/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/28 21:24:24 by nuno             ###   ########.fr       */
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
		;//to do
	else
	{
		while (++i < table->num_of_philos)
			thread_handle(&table->philosophers[i].philo_thread, routine,
				&table->philosophers[i], CREATE);
	}
	// getting the time when simulation starts
	table->start_time = get_time(MILISECONDS);
	// changed the bool of philos_are_ready to true
	change_bool(&table->table_mutex, &table->philos_are_ready, true);
	// wait for every philos to be ready, when they are, we are ready to join
	i = -1;
	while (++i < table->num_of_philos)
		thread_handle(&table->philosophers[i].philo_thread, NULL, NULL, JOIN);
}
