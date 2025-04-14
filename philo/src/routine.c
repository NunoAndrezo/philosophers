/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:29 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/14 10:45:19 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	routine_incepetion(t_philo *philo);

void	*routine(void *philoso)
{
	t_philo	*philo;

	philo = (t_philo *)philoso;
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == false)
		usleep(100);
	change_long(&philo->philo_mutex, &philo->time_last_eat,
		get_time(MILISECONDS));
	increase_long(&philo->table->table_mutex,
		&philo->table->num_threads_running);
	make_a_mf_wait(philo);
	if (routine_incepetion(philo) == 1)
		return (NULL);
	return (NULL);
}

static int	routine_incepetion(t_philo *philo)
{
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == true)
	{
		if (check_bool(&philo->philo_mutex, &philo->full) == true)
			return (1);
		if (check_bool(&philo->philo_mutex, &philo->dead) == true)
		{
			print_mutex(philo, DEAD);
			return (1);
		}
		breakfast(philo);
		ft_zzz(philo);
		if (check_bool(&philo->philo_mutex, &philo->full) == true)
			return (1);
		if (check_bool(&philo->philo_mutex, &philo->dead) == true)
		{
			print_mutex(philo, DEAD);
			return (1);
		}
		iq_rising(philo, true);
	}
	return (1);
}
