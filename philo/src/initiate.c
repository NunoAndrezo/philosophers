/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:29 by nuno              #+#    #+#             */
/*   Updated: 2025/02/22 17:31:22 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	get_arg(t_philo_data *data, int arc, char **arv)
{
	data->num_of_philos = ft_atoi(arv[1]);
	data->num_of_forks = data->num_of_philos;
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	if (arc == 6)
		data->num_must_eat = ft_atoi(arv[5]);
	else
		data->num_must_eat = 0;
}

void	initiate_data(t_philo_data *data)
{
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
	data->philos_created = false;
	data->reached_must_eat = false;
	data->running = false;
	data->forks = NULL;
	//pthread_mutex_init(&data->print, NULL);
}

t_philo	*initiate_philosopher(int n, t_philo *philosopher, t_philo_data *data)
{
	philosopher->id = n + 1;
	philosopher->eat_count = 0;
	philosopher->state.eating = true;
	philosopher->state.sleeping = false;
	philosopher->state.thinking = false;
	philosopher->state.dead = false;
	philosopher->time_last_eat = 0;
	philosopher->data = data;
	return (philosopher);
}
