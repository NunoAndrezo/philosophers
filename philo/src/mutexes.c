/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:00 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/24 23:07:10 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	create_forks(t_philo_data *data)
{
	unsigned int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t *) * data->num_of_forks);
	if (!data->forks)
	{
		write(2, "Error: Malloc failed\n", 21);
		exit(1);
	}
	while (i < data->num_of_forks)
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
		{
			write(2, "Error: Malloc failed\n", 21);
			exit(1); //i cant use exit function, is prohibited
		}
		pthread_mutex_init(data->forks[i], NULL);
		printf("fork %d allocated\n", i);
		fflush(stdout);
		i++;
	}
	printf("forks allocated\n");
	fflush(stdout);
}

void	destroy_forks(t_philo_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_of_forks)
	{
		pthread_mutex_destroy(data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	create_print_mutex(t_philo_data *data)
{
	printf("creating print mutex\n");
	fflush(stdout);
	data->print_state = malloc(sizeof(pthread_mutex_t));
	if (!data->print_state)
	{
		write(2, "Error: Malloc failed\n", 21);
		exit(1);
	}
	pthread_mutex_init(data->print_state, NULL);
}

void	print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->data->print_state);
	printf("%lu %d %s\n", get_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(philo->data->print_state);
}