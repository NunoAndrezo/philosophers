/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:35:55 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/17 23:30:08 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	arroz_de_cabidela(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	print_mutex(philo, FIRST_FORK);
	mutex_handle(&philo->right_fork->fork, LOCK);
	print_mutex(philo, SECOND_FORK);
	change_long(&philo->philo_mutex, &philo->time_last_eat, get_current_time(philo->table->start_time));
	print_mutex(philo, EATING);
	ft_usleep(philo->table->time_to_eat);
	if (philo->table->nr_meals_limit > 0)
		increase_long(&philo->philo_mutex ,&philo->eat_count);
	if (philo->table->nr_meals_limit > 0 && check_long(&philo->philo_mutex, &philo->eat_count) == philo->table->nr_meals_limit)
		change_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}

void	ft_zzz(t_philo *philo)
{
	print_mutex(philo, SLEEPING);
	ft_usleep(philo->table->time_to_sleep);
}

void	thinking_alot(t_philo *philo)
{
	print_mutex(philo, THINKING);
	/*if (philo->id % 2 != 0)
		ft_usleep(2);*/
}
