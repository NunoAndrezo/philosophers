/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:15 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/28 00:41:15 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	rotina_filhote(t_philo *philosopher);
static bool	check_all_philos_have_eaten(t_philo_data *data);

void	*routine(void *philo)
{
	t_philo	*philosopher;

	fflush(stdout);
	philosopher = (t_philo *)philo;
	while (philosopher->data->running == false || philosopher->data->philos_created == false)
		ft_usleep(10, -42);
	while (philosopher->data->running == true && philosopher->data->philos_created == true)
	{
		if (philosopher->data->all_philos_have_eaten == true)
		{
			philosopher->data->running = false;
			return (NULL);
		}
		else if (philosopher->data->reached_must_eat == false)
			rotina_filhote(philosopher);
		else
			return (NULL);
	}
	return (NULL);
}

static void	rotina_filhote(t_philo *philosopher)
{
	pthread_mutex_t	lock;
	unsigned int	i;

	while (philosopher->data->running == true)
	{
		if (philosopher->data->num_must_eat != -42)
		{	
			if (philosopher->eat_count == philosopher->data->num_must_eat)
				philosopher->reached_must_eat = true;
			if (check_all_philos_have_eaten(philosopher->data) == true)
				philosopher->data->all_philos_have_eaten = true;
			if (philosopher->data->all_philos_have_eaten == true)
				return ;
		}
		i = 0;
		while (philosopher->eat_count > philosopher->data->philosophers[i]->eat_count)
		{
			pthread_mutex_init(&lock, NULL);
			pthread_mutex_lock(&lock);
			ft_usleep(100, -42);
			i++;
			if (i == philosopher->data->num_of_philos)
				i = 0;
		}
		pthread_mutex_unlock(&lock);
		pthread_mutex_destroy(&lock);
		if (philosopher->have_not_eaten == true)
			philosopher->time_last_eat = get_time();
		philosopher->have_not_eaten = false;
		if (philosopher->data->running == false || philosopher->data->reached_must_eat == true || philosopher->state.dead == true || (get_time() - philosopher->time_last_eat) > philosopher->data->time_to_die)
			return ;
		philosopher->state.thinking = false;
		philosopher->state.eating = false;
		philosopher->state.sleeping = false;
		pthread_mutex_lock(philosopher->fork_left);
		print_state(philosopher, "has taken a fork");
		if (philosopher->fork_left == NULL || philosopher->fork_right == NULL)
		{
			while (get_time() - philosopher->time_last_eat < philosopher->data->time_to_die)
				ft_usleep(10, -42);
			philosopher->state.dead = true;
			print_state(philosopher, "died");
			philosopher->data->running = false;
			return ;
		}
		pthread_mutex_lock(philosopher->fork_right);
		print_state(philosopher, "has taken a fork");
		if ((get_time() - philosopher->time_last_eat) > philosopher->data->time_to_die)
		{
			philosopher->state.dead = true;
			print_state(philosopher, "died");
			philosopher->data->running = false;
			pthread_mutex_unlock(philosopher->fork_left);
			pthread_mutex_unlock(philosopher->fork_right);
			return ;
		}
		philosopher->state.eating = true;
		print_state(philosopher, "is eating");
		ft_usleep(philosopher->data->time_to_eat, philosopher->time_last_eat);
		philosopher->time_last_eat = get_time();
		pthread_mutex_unlock(philosopher->fork_left);
		pthread_mutex_unlock(philosopher->fork_right);
		if (philosopher->data->num_must_eat != -42)
		{	
			printf("@@@\n");
			fflush(stdout);
			philosopher->eat_count++;
			if (philosopher->eat_count == philosopher->data->num_must_eat)
				philosopher->reached_must_eat = true;
			if (check_all_philos_have_eaten(philosopher->data) == true)
				philosopher->data->all_philos_have_eaten = true;
			if (philosopher->data->all_philos_have_eaten == true)
				return ;
		}
		philosopher->state.eating = false;
		if (philosopher->reached_must_eat == true)
			return ;
		printf("AFTER EATING\n");
		fflush(stdout);
		if (philosopher->data->running == false || (get_time() - philosopher->time_last_eat) > philosopher->data->time_to_die || philosopher->data->reached_must_eat == true || philosopher->state.dead == true)
			return ;
		printf("AFTER EATING 2\n");
		fflush(stdout);
		print_state(philosopher, "is sleeping");
		philosopher->state.sleeping = true;
		ft_usleep(philosopher->data->time_to_sleep, -42);
		philosopher->state.sleeping = false;
		print_state(philosopher, "is thinking");
		philosopher->state.thinking = true;
		if (philosopher->data->num_must_eat != -42
			&& philosopher->eat_count == philosopher->data->num_must_eat)
		{
			print_state(philosopher, "is thinking");
			philosopher->data->reached_must_eat = true;
			return ;
		}
		if ((get_time() - philosopher->time_last_eat) > philosopher->data->time_to_die)
		{
			philosopher->state.dead = true;
			print_state(philosopher, "died");
			philosopher->data->running = false;
			return ;
		}
	}
	if ((get_time() - philosopher->time_last_eat) > philosopher->data->time_to_die)
	{
		philosopher->state.dead = true;
		print_state(philosopher, "died");
		philosopher->data->running = false;
		return ;
	}
}

static bool	check_all_philos_have_eaten(t_philo_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philosophers[i]->reached_must_eat == false)
			return (false);
		i++;
	}
	return (true);
}

/* static bool	 */