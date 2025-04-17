/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners_and_frees.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:01:43 by nuno              #+#    #+#             */
/*   Updated: 2025/04/17 23:36:23 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	vileda(t_table *table)
{
	int	i;

	i = -1;
	if (!table)
		return ;
	if (table->philosophers)
	{
/*		while (++i < table->num_of_philos)
		{
			pthread_mutex_destroy(&table->philosophers[i].philo_mutex);
			pthread_mutex_destroy(&table->forks[i].fork);
		}*/
		free(table->philosophers);
		table->philosophers = NULL;
	}
	/*if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->table_mutex);
	}*/
	free(table);
	table = NULL;
}
