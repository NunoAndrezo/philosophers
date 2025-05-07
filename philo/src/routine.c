/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:29 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/07 22:32:14 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*solo_routine(t_philo *philo);
static void	arroz_de_cabidela(t_philo *philo);
static bool	philo_died(t_philo *philo);
static void	usleep_with_checker(long time, t_philo *philo);

void	*routine(void *philoso)
{
	t_philo	*philo;

	philo = (t_philo *)philoso;
	while (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
		usleep(10);
	if (philo->table->num_of_philos == 1)
		return (solo_routine(philo), NULL);
	if (philo->id % 2 == 0)
		usleep((philo->table->time_to_sleep / 5) * 1000);
	while (1)
	{
		if (philo_died(philo) == true)
			return (NULL);
		if (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
			return (NULL);
		arroz_de_cabidela(philo);
		if (philo_died(philo) == true)
			return (NULL);
		if (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
			return (NULL);
		print_mutex(philo, SLEEPING);
		usleep_with_checker(philo->table->time_to_sleep, philo);
		//usleep_with_checker(philo->table->time_to_sleep, philo);
		if (philo_died(philo) == true)
			return (NULL);
		if (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
			return (NULL);
		print_mutex(philo, THINKING);
		if (philo->table->num_of_philos % 2 != 0 && philo->table->time_to_eat > philo->table->time_to_sleep)
				usleep_with_checker((philo->table->time_to_eat - philo->table->time_to_sleep) + 10, philo);
		if (philo->full == true)
				return (NULL);
	}
	return (NULL);
}

static void	arroz_de_cabidela(t_philo *philo)
{
	if (philo_died(philo) == true)
		return ;
	if (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
		return ;

	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);

	print_mutex(philo, FIRST_FORK);
	print_mutex(philo, SECOND_FORK);
	print_mutex(philo, EATING);
	
	usleep_with_checker(philo->table->time_to_eat, philo);
	philo->time_last_eat = get_current_time(philo->table->start_time);
	
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	increase_long(&philo->table->table_mutex, &philo->eat_count);
	if (philo->table->nr_meals_limit <= philo->eat_count && philo->table->nr_meals_limit > 0)
		philo->full = true;
}

static void	*solo_routine(t_philo *philo)
{
	while (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
		usleep(100);
	print_mutex(philo, FIRST_FORK);
	usleep_with_checker(philo->table->time_to_die, philo);
	print_mutex(philo, DEAD);
	change_bool(&philo->table->table_mutex, &philo->table->running, false);
	return (NULL);
}

static bool	philo_died(t_philo *philo)
{
	long now;
	long elapsed_since_food;

	if (philo->full == true)
		return (false);
	now = get_current_time(philo->table->start_time);
	elapsed_since_food = now - philo->time_last_eat;
	if (elapsed_since_food > philo->table->time_to_die)
	{
		mutex_handle(&philo->table->table_mutex, LOCK);
		if (philo->table->running == false)
		{
			mutex_handle(&philo->table->table_mutex, UNLOCK);
			return (true);
		}
		philo->table->running = false;
		mutex_handle(&philo->table->table_mutex, UNLOCK);
		mutex_handle(&philo->table->print_mutex, LOCK);
		printf(RED"%ld %ld died\n"RESET, now, philo->id);
		mutex_handle(&philo->table->print_mutex, UNLOCK);
		return (true);
	}
	return (false);
}

static void	usleep_with_checker(long time, t_philo *philo)
{
	long	start;
	long	current;

	if (philo->full == true)
		return ;
	start = get_current_time(philo->table->start_time);
	while (1)
	{
		current = get_current_time(philo->table->start_time);
		if (philo_died(philo) == true)
			break ;
		if (current - start >= time)
			break ;
		usleep(60);
	}
}
