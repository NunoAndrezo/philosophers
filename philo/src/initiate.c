/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:29 by nuno              #+#    #+#             */
/*   Updated: 2025/03/20 00:03:36 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	get_arg(t_table *table, int arc, char **arv)
{
	table->num_of_philos = ft_atol(arv[1]);
	table->num_of_forks = table->num_of_philos;
	table->time_to_die = ft_atol(arv[2]);
	table->time_to_eat = ft_atol(arv[3]);
	table->time_to_sleep = ft_atol(arv[4]);
	if (arc == 6)
		table->nr_meals_limit = ft_atol(arv[5]);
	else
		table->nr_meals_limit = -1;
}

t_table	*initiate_data(void)
{
	t_table	*table;
	pthread_mutex_t	lock;
	pthread_mutex_t	check_mtx;
	pthread_mutex_t	helper;
	pthread_mutex_t	philo_dead;
	pthread_mutex_t	philo_eaten;
	
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
	{
		write(2, "Error: Malloc failed\n", 21);
		exit(1);
	}
	pthread_mutex_init(&check_mtx, NULL);
	pthread_mutex_init(&helper, NULL);
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&philo_dead, NULL);
	pthread_mutex_init(&philo_eaten, NULL);
	table->num_of_philos = 0;
	table->num_of_forks = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->nr_meals_limit = 0;
	table->start_time = 0;
	table->running = false;
	table->forks = NULL;
	table->lock = lock;
	table->check_mtx = check_mtx;
	table->helper = helper;
	table->philo_dead = philo_dead;
	table->philo_eaten = philo_eaten;
	return (table);
}
void	initiate_philosopher(int n, t_philo *philosopher, t_table *table)
{
	philosopher->id = n + 1;
	philosopher->eat_count = 0;
	philosopher->dead = false;
	philosopher->time_last_eat = 0;
	philosopher->table = table;
	philosopher->fork_left = NULL;
	philosopher->fork_right = NULL;
	philosopher->have_not_eaten = true;
}
