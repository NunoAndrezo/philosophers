/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:29 by nuno              #+#    #+#             */
/*   Updated: 2025/05/07 21:32:42 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	initiate_philosopher(t_table *table);
static void	assign_forks(t_philo *philo, t_fork *forks, long i);
static void	initiate(t_table *table);

void	get_args_and_initiate(t_table *table, int arc, char **arv)
{
	table->num_of_philos = ft_atol(arv[1]);
	table->num_of_forks = table->num_of_philos;
	table->time_to_die = (ft_atol(arv[2]));
	table->time_to_eat = (ft_atol(arv[3]));
	table->time_to_sleep = (ft_atol(arv[4]));
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
	{
		vileda(table);
		error_and_exit(RED "Use timestamps bigger than 60ms" RESET);
	}
	if (table->num_of_philos <= 0 || table->num_of_philos > 200)
	{
		vileda(table);
		error_and_exit(RED "Number of philosophers [1-200]" RESET);
	}
	if (arc == 6)
		table->nr_meals_limit = ft_atol(arv[5]);
	else
		table->nr_meals_limit = -1;
	initiate(table);
}

static void	initiate(t_table *table)
{
	long	i;

	table->start_time = 0;
	table->running = false;
	mutex_handle(&table->print_mutex, INIT);
	mutex_handle(&table->table_mutex, INIT);
	table->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* table->num_of_philos);
	if (!table->philosophers)
		error_and_exit(RED "Error: Malloc failed" RESET);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_of_forks);
	if (!table->forks)
		error_and_exit(RED "Error: Malloc failed" RESET);
	i = -1;
	while (++i < table->num_of_philos)
		mutex_handle(&table->forks[i].fork, INIT);
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

static void	assign_forks(t_philo *philo, t_fork *forks, long i)
{
	long	philo_nbr;

	philo_nbr = philo->table->num_of_philos;
	//if (philo->id % 2 == 0)
	//{
/*	if (philo_nbr % 2 != 0)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % philo_nbr];
	}
	else*/
	{
		if (philo->id % 2 == 0)
		{
			philo->left_fork = &forks[(i + 1) % philo_nbr];
			philo->right_fork = &forks[i];
		}
		else
		{
			philo->left_fork = &forks[i];
			philo->right_fork = &forks[(i + 1) % philo_nbr];
		}
	}
}
