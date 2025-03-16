/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:22:19 by nuno              #+#    #+#             */
/*   Updated: 2025/03/16 01:52:23 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"

static t_philo	*creation(unsigned int n, t_philo_data *data);

void	creating_philos(t_philo_data *data)
{
	unsigned int	i;
	t_philo		*philo;

	i = 0;
	data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philosophers)
	{
		write(2, "Error: malloc failed\n", 21);
		return ;
	}
	while (i < data->num_of_philos)
	{
		philo = creation(i, data);
		data->philosophers[i] = philo;
		i++;
	}
}

static t_philo	*creation(unsigned int n, t_philo_data *data)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (!philosopher)
	{
		write(2, "Error: malloc failed\n", 21);
		return (NULL);
	}
	initiate_philosopher(n, philosopher, data);
	return (philosopher);
}