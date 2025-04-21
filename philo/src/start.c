/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/21 15:06:29 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start(t_table *table)
{
	long	i;

	if (table->nr_meals_limit == 0)
		return (error_and_exit("Everyone died of hunger"), (void)0);
	if (pthread_create(&table->monitor_thread, NULL, monitor_routine, table) != 0)
	{
		vileda(table);
		error_and_exit(RED "Error: Pthread creation failed" RESET);
	}
	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_create(&table->philosophers[i].philo_thread, NULL, routine,
			&table->philosophers[i]) != 0)
		{
			vileda(table);
			error_and_exit(RED "Error: Malloc failed" RESET);
		}
	}
	change_long(&table->table_mutex, &table->start_time, get_time());
	change_bool(&table->table_mutex, &table->running, true);
	change_bool(&table->table_mutex, &table->philos_are_ready, true);
	if (pthread_join(table->monitor_thread, NULL) != 0)
	{
		vileda(table);
		error_and_exit(RED "Error: Pthread join failed" RESET);
	}
	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_detach(table->philosophers[i].philo_thread) != 0)
		{
			vileda(table);
			error_and_exit(RED "Error: Pthread join failed" RESET);
		}
	}
}
