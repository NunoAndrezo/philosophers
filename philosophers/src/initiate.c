/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:36:29 by nuno              #+#    #+#             */
/*   Updated: 2025/02/03 21:36:31 by nneves-a         ###   ########.fr       */
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
		data->num_must_eat = -1;
}

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

t_philo	*initate_philos(int n, t_philo_data *data)
{
	t_philo		*philosophers;
	pthread_t	thread;

	philosophers->id = n + 1;
	philosophers->eat_count = 0;
	philosophers->state.full = false;
	philosophers->state.awake = false;
	philosophers->state.smart = false;
	philosophers->state.dead = false;
	philosophers->last_eat = data->start_time;
	philosophers->philo_thread = NULL;
	philosophers->next = NULL;
	philosophers->prev = NULL;
}
