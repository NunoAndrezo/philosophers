/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:44:10 by nuno              #+#    #+#             */
/*   Updated: 2025/04/05 18:07:53 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*solo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (check_bool(&philo->table->table_mutex, &philo->table->philos_are_ready) == false)
		usleep(100);
	change_long(&philo->philo_mutex, &philo->time_last_eat, get_time(MILISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->num_threads_running);
	print_mutex(philo, FIRST_FORK);
	while (check_bool(&philo->table->table_mutex, &philo->table->running) == true)
		usleep(100);
	return (NULL);
}