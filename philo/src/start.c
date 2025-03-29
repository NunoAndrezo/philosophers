/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/29 01:55:58 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start(t_table *table)
{
	long	i;

	i = -1;
/* 	if (table->nr_meals_limit == 0)
	{
		printf("return");
		fflush(stdout);
		return ; // back to the main to clean everything
	}
	else if (table->num_of_philos == 1)
		;//to do later */
// else
	table->start_time = get_time(MILISECONDS);
	while (++i < table->num_of_philos)
		pthread_create(&table->philosophers[i].philo_thread, NULL, routine, &table->philosophers[i]);
//
	i = -1;
	pthread_mutex_lock(&table->table_mutex);
	table->philos_are_ready = true;
	table->running = true;
	pthread_mutex_unlock(&table->table_mutex);
	while (++i < table->num_of_philos)
		pthread_join(table->philosophers[i].philo_thread, NULL);
}
