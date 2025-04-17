/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:29 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/17 23:29:42 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	actual_routine(t_philo *philo);
static void	make_them_wait(t_philo *philo);
static void	*solo_routine(t_philo *philo);

void	*routine(void *philoso)
{
	t_philo	*philo;

	philo = (t_philo *)philoso;
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == false)
		usleep(100);
	increase_long(&philo->table->table_mutex,
		&philo->table->num_threads_running);
	if (philo->table->num_of_philos == 1)
	{
		solo_routine(philo);
		return (NULL);
	}
	make_them_wait(philo);
	actual_routine(philo);
	return (NULL);
}

static void	*solo_routine(t_philo *philo)
{
	print_mutex(philo, FIRST_FORK);
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == true)
		usleep(100);
	return (NULL);
}

static void	actual_routine(t_philo *philo)
{
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == true)
	{
		if (check_bool(&philo->philo_mutex, &philo->full) == true)
			return ;
		if (check_bool(&philo->philo_mutex, &philo->dead) == true)
		{
			print_mutex(philo, DEAD);
			return ;
		}
/*		if (philo->id % 2 != 0)
			ft_usleep(2);*/
		arroz_de_cabidela(philo);
		ft_zzz(philo);
		if (check_bool(&philo->philo_mutex, &philo->full) == true)
			return ;
		if (check_bool(&philo->philo_mutex, &philo->dead) == true)
		{
			print_mutex(philo, DEAD);
			return ;
		}
		thinking_alot(philo);
	}
	return ;
}

static void	make_them_wait(t_philo *philo)
{
	/*if (philo->table->num_of_philos % 2 == 0 && philo->id % 2 != 0)
		ft_usleep(philo->table->time_to_sleep);
	else if (philo->table->num_of_philos % 2 != 0 && philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_sleep);*/
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_sleep);
}
