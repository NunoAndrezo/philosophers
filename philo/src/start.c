/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/24 22:32:32 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	join_threads(t_philo_data *data);
static void	create_threads(t_philo_data *data);
static pthread_t	pthreads_creation(t_philo *philosopher);

void	start(t_philo_data *data)
{
	create_forks(data);
	create_print_mutex(data);
	create_threads(data);
	data->running = true;
	data->start_time = get_time();
	printf("Simulation started\n");
	fflush(stdout);
	join_threads(data);
}
static void	create_threads(t_philo_data *data)
{
	unsigned int	i;
	
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philosophers[i]->philo_thread = pthreads_creation(data->philosophers[i]);
		i++;
	}
}

static pthread_t	pthreads_creation(t_philo *philosopher)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &routine, philosopher);
	return (thread);
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