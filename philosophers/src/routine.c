/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:15 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/17 17:10:41 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *philo)
{
	t_philo	*philosopher;

	printf("dentro da rotina\n");
	fflush(stdout);
	philosopher = (t_philo *)philo;
	while (philosopher->data->running == false
		|| philosopher->data->ready_to_start == false)
		ft_usleep(100);
	if (philosopher->data->running == true
		&& philosopher->data->ready_to_start == true)
	{
		grabbing_forks(philosopher);
	}
	return (NULL);
}

void	grabbing_forks(t_philo *philosopher)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	unsigned int	i;

	i = 0;
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
	philosopher->state.sleeping = true;
	ft_usleep(philosopher->data->time_to_sleep);
	philosopher->state.sleeping = false;
	philosopher->state.thinking = true;
	if (philosopher->data->num_must_eat != 0
		&& philosopher->eat_count == philosopher->data->num_must_eat)
	{
		print_state(philosopher, "is thinking");
		return ;
	}

}
