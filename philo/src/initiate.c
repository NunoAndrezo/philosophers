/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:29 by nuno              #+#    #+#             */
/*   Updated: 2025/03/28 21:27:31 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	initiate_philosopher(t_table *table);
static void assign_forks(t_philo *philo, t_fork *forks, long philo_index);

void	get_arg(t_table *table, int arc, char **arv)
{
	table->num_of_philos = ft_atol(arv[1]);
	table->num_of_forks = table->num_of_philos;
	table->time_to_die = ft_atol(arv[2]) * 1e3;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_and_exit(RED"Use timestamps major than 60ms"RESET);
	table->time_to_eat = ft_atol(arv[3]) * 1e3;
	table->time_to_sleep = ft_atol(arv[4]) * 1e3;
	if (arc == 6)
		table->nr_meals_limit = ft_atol(arv[5]);
	else
		table->nr_meals_limit = -1;
}

void	initiate(t_table	*table)
{
	long	i;

	i = -1;
	table->start_time = 0;
	table->philos_are_ready = false;
	table->running = false;
	mutex_handle(&table->print_mutex, INIT);
	mutex_handle(&table->table_mutex, INIT);
	mutex_handle(&table->checker, INIT);
	table->philosophers = (t_philo *)malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philosophers)
		error_and_exit(RED"Error: Malloc failed"RESET);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_of_forks);
	if (!table->forks)
		error_and_exit(RED"Error: Malloc failed"RESET);
	while (++i < table->num_of_philos)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].id = i + 1;
	}
	initiate_philosopher(table);
}

static void	initiate_philosopher(t_table *table)
{
	long	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_of_philos)
	{
		philo = table->philosophers + i; // if doesnt work, try philo = table->philosophers + i;
		philo->id = i + 1;
		philo->full = false;
		philo->eat_count = 0;
		philo->table = table;
		philo->time_last_eat = 0;
		mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
	
}

static void assign_forks(t_philo *philo, t_fork *forks, long philo_index)
{
	long	philo_nbr;

	philo_nbr = philo->table->num_of_philos;
	philo->first_fork = &forks[(philo_index + 1) % philo_nbr]; // 1+1 / 10 = 0,2 o resto e 2. // 3 + 1 / 10 = 0,4 o resto e 4 // 5 + 1 / 10 = 0,6 o resto e 6 // 7 + 1 / 10 = 0,8 o resto e 8 // 9 + 1 / 10 = 0,10 o resto e 0
	philo->second_fork = &forks[philo_index];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_index];
		philo->second_fork = &forks[(philo_index + 1) % philo_nbr]; // 2 + 1 / 10 = 0,3 o resto e 3 // 4 + 1 / 10 = 0,5 o resto e 5 // 6 + 1 / 10 = 0,7 o resto e 7 // 8 + 1 / 10 = 0,9 o resto e 9 // 10 + 1 / 10 = 0,11 o resto e 1
	}
}
