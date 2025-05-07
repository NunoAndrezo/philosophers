/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/07 20:50:19 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start(t_table *table)
{
	long	i;

	if (table->nr_meals_limit == 0)
		return (vileda(table), error_and_exit("Everyone died of hunger"), (void)0);
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
	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_join(table->philosophers[i].philo_thread, NULL) != 0)
		{
			vileda(table);
			error_and_exit(RED "Error: Pthread join failed" RESET);
		}
	}
}
