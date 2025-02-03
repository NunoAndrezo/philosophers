/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:22:19 by nuno              #+#    #+#             */
/*   Updated: 2025/02/03 21:36:34 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"


void creating_philos(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philosophers[i] = creation(data, i);
	}
}

t_philo	*creation(t_philo_data *data, int n)
{
	t_philo	*philosophers;

	philosophers = initiate_philos(n, data);
}