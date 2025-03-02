/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:40:15 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/02 01:35:34 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	rotina_filhote(t_philo *philosopher);
static bool	check_all_philos_have_eaten(t_philo_data *data);
static bool check_if_philo_is_dead(t_philo *philosopher, bool with_forks);

void	*routine(void *philo)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)philo;

	// Check for NULL pointers to avoid segmentation faults
	if (philosopher == NULL || philosopher->data == NULL || philosopher->fork_left == NULL) {
		printf("Error: Invalid philosopher or fork pointer\n");
		return NULL;
	}
	printf("Philosopher %d is alive\n", philosopher->id);
	fflush(stdout);
	while (philosopher->data->running == false || philosopher->data->philos_created == false)
		ft_usleep(10, -42);
	while (philosopher->data->running == true && philosopher->data->philos_created == true)
	{
		pthread_mutex_lock(&philosopher->data->lock);
		if (philosopher->data->all_philos_have_eaten == true)
		{
		philosopher->data->running = false;
		pthread_mutex_unlock(&philosopher->data->lock);
		return (NULL);
		}
		pthread_mutex_unlock(&philosopher->data->lock);
		if (philosopher->data->reached_must_eat == false)
			rotina_filhote(philosopher);
		else
			return (NULL);
	}
	return (NULL);
}

static void	rotina_filhote(t_philo *philosopher)
{
	unsigned int	i;

	while (philosopher->data->running == true)
	{
		pthread_mutex_lock(&philosopher->data->lock);
		if (philosopher->data->num_must_eat != -42)
		{	
		if (philosopher->eat_count == philosopher->data->num_must_eat)
			philosopher->reached_must_eat = true;
		if (check_all_philos_have_eaten(philosopher->data) == true)
		{
			philosopher->data->all_philos_have_eaten = true;
			pthread_mutex_unlock(&philosopher->data->lock);
			return ;
		}
		}
		pthread_mutex_unlock(&philosopher->data->lock);

		if (philosopher->reached_must_eat == true)
		return ;

		pthread_mutex_lock(&philosopher->data->lock);
		i = 0;
		while (philosopher->eat_count > philosopher->data->philosophers[++i]->eat_count)
		{
		if (i == philosopher->data->num_of_philos)
			i = 0;
		}
		pthread_mutex_unlock(&philosopher->data->lock);

		if (philosopher->have_not_eaten == true)
		philosopher->time_last_eat = get_time();
		philosopher->have_not_eaten = false;

		if (check_if_philo_is_dead(philosopher, false) == true)
		{
		philosopher->data->running = false;
		return ;
		}

		if (philosopher->data->running == false || philosopher->data->reached_must_eat == true || check_if_philo_is_dead(philosopher, false) == true)
		return ;

		pthread_mutex_lock(philosopher->fork_left);
		print_state(philosopher, "has taken a fork");

		if (philosopher->fork_right == NULL)
		{
			while (get_time() - philosopher->time_last_eat < philosopher->data->time_to_die)
				ft_usleep(10, -42);
			philosopher->dead = true;
			print_state(philosopher, "died");
			philosopher->data->running = false;
			pthread_mutex_unlock(philosopher->fork_left);
			return ;
		}
		if (pthread_mutex_trylock(philosopher->fork_right) != 0)
		{
			pthread_mutex_unlock(philosopher->fork_left); // Release the first fork
			ft_usleep(10, -42); // Wait and retry
			continue;
		}
		print_state(philosopher, "has taken a fork");
		if (check_if_philo_is_dead(philosopher, true) == true)
			return ;
		print_state(philosopher, "is eating");
		ft_usleep(philosopher->data->time_to_eat, philosopher->time_last_eat);
		philosopher->time_last_eat = get_time();
		pthread_mutex_unlock(philosopher->fork_left);
		pthread_mutex_unlock(philosopher->fork_right);
		pthread_mutex_lock(&philosopher->data->lock);
		if (philosopher->data->num_must_eat != -42)
		{
			philosopher->eat_count++;
			if (philosopher->eat_count == philosopher->data->num_must_eat)
				philosopher->reached_must_eat = true;
			if (check_all_philos_have_eaten(philosopher->data) == true)
			{	
				philosopher->data->all_philos_have_eaten = true;
				pthread_mutex_unlock(&philosopher->data->lock);
				return ;
			}
		}
		pthread_mutex_unlock(&philosopher->data->lock);
		if (philosopher->reached_must_eat == true)
			return ;
		if (philosopher->data->running == false || check_if_philo_is_dead(philosopher, false) == true || philosopher->data->reached_must_eat == true)
			return ;
		print_state(philosopher, "is sleeping");
		ft_usleep(philosopher->data->time_to_sleep, -42);
		print_state(philosopher, "is thinking");
		if (philosopher->data->num_must_eat != -42 && philosopher->eat_count == philosopher->data->num_must_eat)
		{
			print_state(philosopher, "is thinking");
			philosopher->data->reached_must_eat = true;
			return ;
		}
		check_if_philo_is_dead(philosopher, false);
	}
}

static bool	check_all_philos_have_eaten(t_philo_data *data)
{
    unsigned int	i;
    bool all_eaten = true;

    pthread_mutex_lock(&data->lock);
    for (i = 0; i < data->num_of_philos; i++)
    {
        if (data->philosophers[i]->reached_must_eat == false)
        {
            all_eaten = false;
            break;
        }
    }
    pthread_mutex_unlock(&data->lock);
    return all_eaten;
}

static bool check_if_philo_is_dead(t_philo *philosopher, bool with_forks)
{
    uint64_t time_since_last_meal = get_time() - philosopher->time_last_eat;

    if (time_since_last_meal > philosopher->data->time_to_die)
    {
        pthread_mutex_lock(&philosopher->data->lock);
        philosopher->dead = true;
        print_state(philosopher, "died");
        philosopher->data->running = false;
        pthread_mutex_unlock(&philosopher->data->lock);

        if (with_forks)
        {
            pthread_mutex_unlock(philosopher->fork_left);
            pthread_mutex_unlock(philosopher->fork_right);
        }
        return true;
    }
    return false;
}

/* 
static void	rotina_filhote(t_philo *philosopher);
static bool	check_all_philos_have_eaten(t_philo_data *data);
static bool check_if_philo_is_dead(t_philo *philosopher, bool with_forks);

void	*routine(void *philo)
{
	t_philo	*philosopher;

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
	unsigned int	i;

	while (philosopher->data->running == true)
	{
		if (philosopher->data->num_must_eat != -42)
		{	
			if (philosopher->eat_count == philosopher->data->num_must_eat)
				philosopher->reached_must_eat = true;
			if (check_all_philos_have_eaten(philosopher->data) == true)
			{
				philosopher->data->all_philos_have_eaten = true;
				return ;
			}
		}
		if (philosopher->reached_must_eat == true)
			return ;
		pthread_mutex_lock(&philosopher->data->lock);
		i = 0;
		while (philosopher->eat_count > philosopher->data->philosophers[++i]->eat_count)
		{
			if (i == philosopher->data->num_of_philos)
				i = 0;
		}
		pthread_mutex_unlock(&philosopher->data->lock);
		if (philosopher->have_not_eaten == true)
			philosopher->time_last_eat = get_time();
		philosopher->have_not_eaten = false;
		if (check_if_philo_is_dead(philosopher, false) == true)
		{
			philosopher->data->running = false;
			return ;
		}
		if (philosopher->data->running == false || philosopher->data->reached_must_eat == true || check_if_philo_is_dead(philosopher, false) == true)
			return ;
		pthread_mutex_lock(philosopher->fork_left);
		print_state(philosopher, "has taken a fork");
		if (philosopher->fork_right == NULL)
		{
			while (get_time() - philosopher->time_last_eat < philosopher->data->time_to_die)
				ft_usleep(10, -42);
			philosopher->dead = true;
			print_state(philosopher, "died");
			philosopher->data->running = false;
			pthread_mutex_unlock(philosopher->fork_right);
			return ;
		}
		pthread_mutex_lock(philosopher->fork_right);
		print_state(philosopher, "has taken a fork");
		check_if_philo_is_dead(philosopher, true);
		print_state(philosopher, "is eating");
		ft_usleep(philosopher->data->time_to_eat, philosopher->time_last_eat);
		philosopher->time_last_eat = get_time();
		pthread_mutex_unlock(philosopher->fork_left);
		pthread_mutex_unlock(philosopher->fork_right);
		if (philosopher->data->num_must_eat != -42)
		{
			philosopher->eat_count++;
			if (philosopher->eat_count == philosopher->data->num_must_eat)
				philosopher->reached_must_eat = true;
			if (check_all_philos_have_eaten(philosopher->data) == true)
			{	
				philosopher->data->all_philos_have_eaten = true;
				return ;
			}
		}
		if (philosopher->reached_must_eat == true)
			return ;
		if (philosopher->data->running == false || check_if_philo_is_dead(philosopher, false) == true || philosopher->data->reached_must_eat == true)
			return ;
		print_state(philosopher, "is sleeping");
		ft_usleep(philosopher->data->time_to_sleep, -42);
		print_state(philosopher, "is thinking");
		if (philosopher->data->num_must_eat != -42
			&& philosopher->eat_count == philosopher->data->num_must_eat)
		{
			print_state(philosopher, "is thinking");
			philosopher->data->reached_must_eat = true;
			return ;
		}
		check_if_philo_is_dead(philosopher, false);
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

static bool check_if_philo_is_dead(t_philo *philosopher, bool with_forks)
{
	if ((get_time() - philosopher->time_last_eat) > philosopher->data->time_to_die && with_forks == true)
	{
		philosopher->dead = true;
		print_state(philosopher, "died");
		philosopher->data->running = false;
		pthread_mutex_unlock(philosopher->fork_left);
		pthread_mutex_unlock(philosopher->fork_right);
		return (true);
	}
	else if ((get_time() - philosopher->time_last_eat) > philosopher->data->time_to_die && with_forks == false)
	{
		philosopher->dead = true;
		print_state(philosopher, "died");
		philosopher->data->running = false;
		return (true);
	}
	return (false);
} */