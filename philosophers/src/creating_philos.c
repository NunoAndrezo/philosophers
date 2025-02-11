/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:22:19 by nuno              #+#    #+#             */
/*   Updated: 2025/02/11 22:42:41 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"

static t_philo	*creation(unsigned int n, t_philo_data *data);

void	creating_philos(t_philo_data *data)
{
	unsigned int	i;
	t_philo		*philo;
	pthread_t		thread;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo = creation(i, data);
		philo->philo_thread = thread;
		pthread_create(&thread, NULL, &routine, philo);
		data->philosophers[i] = philo;
		i++;
	}
	data->ready_to_start = true;
	join_threads(data);
}

static t_philo	*creation(unsigned int n, t_philo_data *data)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	philosopher = initiate_philosopher(n, philosopher, data);

	return (philosopher);
}

void	join_threads(t_philo_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philosophers[i]->philo_thread, NULL);
		i++;
	}
}