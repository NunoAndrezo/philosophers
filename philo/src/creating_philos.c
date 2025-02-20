/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:22:19 by nuno              #+#    #+#             */
/*   Updated: 2025/02/20 21:25:25 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"

static t_philo	*creation(unsigned int n, t_philo_data *data);
static bool	join_threads(t_philo_data *data, unsigned int i);

void	creating_philos(t_philo_data *data)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo = creation(i, data);
		data->philosophers[i] = philo;
		printf("philo id: %d created\n", i + 1);
		fflush(stdout);
		i++;
	}
	data->philos_created = true;
}

static t_philo	*creation(unsigned int n, t_philo_data *data)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	philosopher = initiate_philosopher(n, philosopher, data);

	return (philosopher);
}