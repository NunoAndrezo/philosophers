/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/21 15:35:46 by nuno             ###   ########.fr       */
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
		;//to do
	else
	{
		while (++i < table->num_of_philos)
			thread_handle(&table->philosophers[i].philo_thread, routine,
				&table->philosophers[i], CREATE);
	}
	change_bool(&table->table_mutex, &table->philos_are_ready, true);
	table->running = true;
	table->start_time = get_time();
}
