/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:35:55 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/14 10:36:27 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	breakfast(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	print_mutex(philo, FIRST_FORK);
	mutex_handle(&philo->right_fork->fork, LOCK);
	print_mutex(philo, SECOND_FORK);
	change_long(&philo->philo_mutex, &philo->time_last_eat,
		get_time(MILISECONDS));
	philo->eat_count++;
	print_mutex(philo, EATING);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (check_long(&philo->table->table_mutex,
			&philo->table->nr_meals_limit) > 0
		&& check_long(&philo->philo_mutex,
			&philo->eat_count) == philo->table->nr_meals_limit)
		change_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}

void	ft_zzz(t_philo *philo)
{
	print_mutex(philo, SLEEPING);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	iq_rising(t_philo *philo, bool did_routine_start)
{
	long	t_to_sleep;
	long	t_to_eat;
	long	t_to_think;

	if (did_routine_start == true)
		print_mutex(philo, THINKING);
	if (philo->table->num_of_philos % 2 == 0)
		return ;
	t_to_sleep = philo->table->time_to_sleep;
	t_to_eat = philo->table->time_to_eat;
	t_to_think = ((t_to_eat * 2) - t_to_sleep);
	if (t_to_think < 0)
		t_to_think = 0;
	ft_usleep((t_to_think * 0.42), philo->table);
}

//we use 30000 because its half of the 60mili requirment we established
void	make_a_mf_wait(t_philo *philo)
{
	if (philo->table->num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30000, philo->table);
	}
	else
	{
		if (philo->id % 2 != 0)
			iq_rising(philo, false);
	}
}
