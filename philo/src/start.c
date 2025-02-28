/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/27 23:02:37 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	join_threads(t_philo_data *data);
static void	create_threads(t_philo_data *data);
static void	initiating_forks(t_philo_data *data);

void	start(t_philo_data *data)
{
	create_print_mutex(data);
	create_forks_mutex(data);
	initiating_forks(data);
	data->running = true;
	data->start_time = get_time();
	create_threads(data);
	join_threads(data);
}
static void	initiating_forks(t_philo_data *data)
{
	unsigned int	i;
	
	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philosophers[i]->id == data->num_of_philos)
		{
			data->philosophers[i]->fork_left = data->forks[0];
			data->philosophers[i]->fork_right = data->forks[data->philosophers[i]->id - 1];
			if (data->philosophers[i]->fork_left == data->philosophers[i]->fork_right)
				data->philosophers[i]->fork_right = NULL;
		}
		else if (data->philosophers[i]->id % 2 == 0)
		{
			data->philosophers[i]->fork_left = data->forks[(data->philosophers[i]->id - 1)];
			data->philosophers[i]->fork_right = data->forks[data->philosophers[i]->id];
		}
		else
		{
			data->philosophers[i]->fork_left = data->forks[data->philosophers[i]->id - 1];
			data->philosophers[i]->fork_right = data->forks[(data->philosophers[i]->id)];
		}
		i++;
	}
}

static void	create_threads(t_philo_data *data)
{
	unsigned int	i;
	
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philosophers[i]->philo_thread, NULL, &routine, data->philosophers[i]);
		i++;
	}
}

static void	join_threads(t_philo_data *data)
{
	unsigned int	i;
	
	i = 0;
	if (data->philos_created == 1 && data->running == 1)
	{
		while (i < data->num_of_philos)
		{
			pthread_join(data->philosophers[i]->philo_thread, NULL);
			i++;
		}
		
	}
}