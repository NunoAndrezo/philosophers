/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/20 21:46:20 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
void	create_threads(t_philo_data *data)
{
	pthread_t		thread;
	unsigned int	i;
	
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philosophers[i]->philo_thread = pthreads_creation(data->philosophers[i]);
		i++;
	}
}

pthread_t	pthreads_creation(t_philo *philosopher)
{
	pthread_t		thread;

	pthread_create(&thread, NULL, &routine, philosopher);
	return (thread);
}

static bool	join_threads(t_philo_data *data)
{
	unsigned int	i;
	
	i = 0;
	if (data->philos_created == 1 && data->running == 1)
	{
		while (i < data->num_of_philos)
		{
			pthread_join(data->philosophers[i]->philo_thread, NULL);
			printf("philo id: %d joined\n", i + 1);
			i++;
		}
		
	}
	return (1);
}