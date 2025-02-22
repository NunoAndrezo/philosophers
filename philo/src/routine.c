/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:15 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/22 17:30:48 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *philo)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)philo;
	while (philosopher->data->running == false || philosopher->data->philos_created == false)
		ft_usleep(10);
	if (philosopher->data->running == true && philosopher->data->philos_created == true)
	{
		if (philosopher->data->reached_must_eat == false)
			grabbing_forks(philosopher);
		else
			return (NULL);
	}
	return (NULL);
}

void	grabbing_forks(t_philo *philosopher)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	unsigned int	i;

	i = 0;
	while (philosopher->data->running == true)
	{
		if (philosopher->id % 2 == 0)
		{
			fork_left = philosopher->data->forks[(philosopher->id + 1)];
			fork_right = philosopher->data->forks[philosopher->id];
		}
		else
		{
			fork_left = philosopher->data->forks[philosopher->id];
			fork_right = philosopher->data->forks[(philosopher->id + 1)];
		}
		while (philosopher->eat_count > philosopher->data->philosophers[i]->eat_count)
		{
			ft_usleep(100);
			i++;
			if (i == philosopher->data->num_of_philos)
				i = 0;
		}
		pthread_mutex_lock(fork_left);
		print_state(philosopher, "has taken a fork");
		pthread_mutex_lock(fork_right);
		print_state(philosopher, "has taken a fork");
		if (philosopher->time_last_eat - get_time() > philosopher->data->time_to_die)
		{
			philosopher->state.dead = true;
			print_state(philosopher, "died");
			philosopher->data->running = false;
			pthread_mutex_unlock(fork_left);
			pthread_mutex_unlock(fork_right);
			return ;
		}
		philosopher->state.eating = true;
		print_state(philosopher, "is eating");
		if (philosopher->data->num_must_eat != 0)
			philosopher->eat_count++;
		ft_usleep(philosopher->data->time_to_eat);
		philosopher->time_last_eat = get_time();
		pthread_mutex_unlock(fork_left);
		pthread_mutex_unlock(fork_right);
		philosopher->state.eating = false;
		print_state(philosopher, "is sleeping");
		philosopher->state.sleeping = true;
		ft_usleep(philosopher->data->time_to_sleep);
		philosopher->state.sleeping = false;
		print_state(philosopher, "is thinking");
		philosopher->state.thinking = true;
		if (philosopher->data->num_must_eat != 0
			&& philosopher->eat_count == philosopher->data->num_must_eat)
		{
			print_state(philosopher, "is thinking");
			philosopher->data->reached_must_eat = true;
			return ;
		}
	}
}
