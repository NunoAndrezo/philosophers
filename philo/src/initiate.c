/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:29 by nuno              #+#    #+#             */
/*   Updated: 2025/03/20 21:23:53 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	initiate_philosopher(t_table *table);

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

void	initiate_table(t_table	*table)
{
	long	i;

	i = -1;
	table->philosophers = (t_philo *)malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philosophers)
		error_and_exit(RED"Error: Malloc failed"RESET);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_of_forks);
	if (!table->forks)
		error_and_exit(RED"Error: Malloc failed"RESET);
	table->start_time = 0;
	table->running = false;
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
		philo = table->philosophers + i;
		philo->id = i + 1;
		philo->full = false;
		philo->eat_count = 0;
		philo->table = table;
		philo->time_last_eat = 0;
		assign_forks(philo, table->forks, i);
	}
	
}

static void assign_forks(t_philo *philo, t_fork *forks, long philo_pos)
{
	long	philo_nbr;

	philo_nbr = philo->table->num_of_philos;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}
