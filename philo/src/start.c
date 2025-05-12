/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/12 01:16:21 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	start(t_table *table)
{
	long	i;

	if (table->nr_meals_limit == 0)
		return (vileda(table), ft_error(RED "Everyone died of hunger" RESET));
	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_create(&table->philosophers[i].philo_thread, NULL, routine,
				&table->philosophers[i]) != 0)
			return (vileda(table), ft_error(RED "Malloc failed" RESET));
		table->num_of_threads_running++;
	}
	while (table->num_of_threads_running < table->num_of_philos)
		;
	change_long(&table->table_mutex, &table->start_time, get_time());
	change_bool(&table->table_mutex, &table->running, true);
	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_join(table->philosophers[i].philo_thread, NULL) != 0)
				return (vileda(table), ft_error(RED "Pthread join failed" RESET));
	}
	return (0);
}
