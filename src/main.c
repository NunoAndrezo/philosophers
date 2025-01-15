/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/01/13 21:37:00 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philo_data	*initiate_date(void);

int	main(int arc, char **arv)
{
	t_philo_data	*data;

	data = initiate_data();
	if ( arc == 5 || arc == 6)
	{
		arv[1]
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	return (0);
}

t_philo_data	*initiate_date(void)
{
	t_philo_data	*data;

	data = (t_philo_data *)malloc(sizeof(t_philo_data));
	if (!data)
	{
		write(2, "Error: Malloc failed\n", 21);
		exit(1);
	}
	data->num_of_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->num_eat = 0;
	data->is_dead = false;
	data->start_time = 0;
	data->philos = NULL;
	data->forks = NULL;
	pthread_mutex_init(&data->print, NULL);
	return (data);
}