/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:29:29 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/08 22:32:14 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	thinking(t_philo *philo);
static void	arroz_de_cabidela(t_philo *philo);
static bool	checker_helper(t_philo *philo);

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->table->num_of_philos == 1)
		return (solo_routine(philo), NULL);
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == false);
	if (philo->id % 2 == 0)
		usleep(5 * 1000);
	while (1)
	{
		if (checker_helper(philo))
			return (NULL);
		arroz_de_cabidela(philo);
		if (checker_helper(philo) == true)
			return (NULL);
		print_mutex(philo, SLEEPING);
		usleep_with_checker(philo->table->time_to_sleep, philo);
		if (checker_helper(philo))
			return (NULL);
		thinking(philo);
		if (philo->full == true)
			return (NULL);
	}
	return (NULL);
}

static void	arroz_de_cabidela(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);
	print_mutex(philo, FIRST_FORK);
	print_mutex(philo, SECOND_FORK);
	print_mutex(philo, EATING);
	usleep_with_checker(philo->table->time_to_eat, philo);
	philo->time_last_eat = get_current_time(philo->table->start_time);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	philo->eat_count++;
	if (philo->table->nr_meals_limit
		<= philo->eat_count && philo->table->nr_meals_limit > 0)
		philo->full = true;
}

static void	thinking(t_philo *philo)
{
	long	wait_time;

	print_mutex(philo, THINKING);
	pthread_mutex_lock(&philo->table->table_mutex);
	wait_time = philo->table->time_to_eat - philo->table->time_to_sleep;
	if (wait_time <= 0)
		wait_time = 2;
	if (philo->table->num_of_philos % 2 != 0
		&& philo->table->time_to_eat >= philo->table->time_to_sleep)
		usleep(wait_time * 1000);
	pthread_mutex_unlock(&philo->table->table_mutex);
}

bool	philo_died(t_philo *philo)
{
	long	now;
	long	elapsed_since_food;

	if (philo->full == true)
		return (false);
	now = get_current_time(philo->table->start_time);
	elapsed_since_food = now - philo->time_last_eat;
	if (elapsed_since_food > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->table_mutex);
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

static bool	checker_helper(t_philo *philo)
{
	if (philo_died(philo) == true)
		return (true);
	if (check_bool(&philo->table->table_mutex,
			&philo->table->running) == false)
		return (true);
	return (false);
}
