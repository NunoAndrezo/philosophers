/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:29 by nuno              #+#    #+#             */
/*   Updated: 2025/01/30 00:09:12 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philo_data	*initiate_data(void)
{
	t_philo_data	*data;

	data = (t_philo_data *)malloc(sizeof(t_philo_data));
	if (!data)
	{
		write(2, "Error: Malloc failed\n", 21);
		exit(1);
	}
	data->num_of_philos = 0;
	data->num_of_forks = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->num_must_eat = 0;
	data->start_time = 0;
	data->forks = NULL;
	//pthread_mutex_init(&data->print, NULL);
	return (data);
}

t_philo	*initate_philos(t_philo *philosophers, int n, t_philo_data *data)
{
	philosophers->id = n + 1;
	philosophers->eat_count = 0;
	philosophers->last_eat = data->start_time;
	philosophers->state.is_eating = false;
	philosophers->state.is_sleeping = false;
	philosophers->state.is_thinking = false;
	philosophers->state.is_dead = false;
	philosophers->next = NULL;
	philosophers->prev = NULL;
}
