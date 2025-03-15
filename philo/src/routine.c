#include "../include/philosophers.h"

static void	rotina_filhote(t_philo *philosopher);
static bool	check_all_philos_have_eaten(t_philo_data *data);
static bool check_if_philo_is_dead(t_philo *philosopher, bool with_forks);
//static void ft_changer(pthread_mutex_t ola, bool *runing, bool check);

void	*routine(void *philo)
{
	t_philo		*philosopher;

	philosopher = (t_philo *)philo;
	pthread_mutex_lock(&philosopher->data->lock);
	if (philosopher == NULL || philosopher->data == NULL || philosopher->fork_left == NULL)
	{
		printf("Error: Invalid philosopher or fork pointer\n");
		return NULL;
	}
	while (philosopher->data->running == false || philosopher->data->philos_created == false)
		ft_usleep(10, -42);
	pthread_mutex_unlock(&philosopher->data->lock);
	while (1)
	{
		pthread_mutex_lock(&philosopher->data->lock);
		if (philosopher->data->running == false)
		{
			pthread_mutex_unlock(&philosopher->data->lock);
			return (NULL);
		}
		if (philosopher->eat_count == philosopher->data->num_must_eat)
		{
			if (philosopher->reached_must_eat == false)
				philosopher->reached_must_eat = true;
			pthread_mutex_unlock(&philosopher->data->lock);
			return (NULL);
		}
		philosopher->data->all_philos_have_eaten = check_all_philos_have_eaten(philosopher->data);
		if (philosopher->data->all_philos_have_eaten == true)
		{
			philosopher->data->running = false;
			pthread_mutex_unlock(&philosopher->data->lock);
			return (NULL);
		}
		if (philosopher->data->reached_must_eat == true)
			return (NULL);
		pthread_mutex_unlock(&philosopher->data->lock);
		rotina_filhote(philosopher);
	}
	return (NULL);
}

static void	rotina_filhote(t_philo *philosopher)
{
	unsigned int	i;

	pthread_mutex_lock(&philosopher->data->lock);
	philosopher->data->all_philos_have_eaten = check_all_philos_have_eaten(philosopher->data);
	if (philosopher->eat_count >= philosopher->data->num_must_eat)
	{	
		philosopher->reached_must_eat = true;
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	if (philosopher->data->all_philos_have_eaten == true)
	{
		philosopher->data->running = false;
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	i = 0;
	while (i < philosopher->data->num_of_philos)
	{
		if (philosopher->eat_count <= philosopher->data->philosophers[i]->eat_count)
			break ;
		i++;
	}
	if (philosopher->have_not_eaten == true)
		philosopher->time_last_eat = get_time();
	philosopher->have_not_eaten = false;
	pthread_mutex_unlock(&philosopher->data->lock);
	pthread_mutex_lock(&philosopher->data->lock);
	if (philosopher->data->running == false || check_if_philo_is_dead(philosopher, false) == true)
	{	
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	if (philosopher->data->reached_must_eat == true)
	{
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	pthread_mutex_unlock(&philosopher->data->lock);
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
	if(pthread_mutex_lock(philosopher->fork_right) != 0) //not successful tentar while
	{
		ft_usleep(10, -42); // Wait and retry
		if (pthread_mutex_lock(philosopher->fork_right) != 0)
		{
			pthread_mutex_unlock(philosopher->fork_left); // Release the first fork
			return ;
		}
		if (check_if_philo_is_dead(philosopher, false) == true)
		{
			pthread_mutex_unlock(philosopher->fork_left); // Release the first fork
			return ;	
		}
	}
	print_state(philosopher, "has taken a fork");
	print_state(philosopher, "is eating");
	ft_usleep(philosopher->data->time_to_eat, philosopher->time_last_eat);
	philosopher->time_last_eat = get_time();
	pthread_mutex_lock(&philosopher->data->lock);
	philosopher->eat_count++;
	pthread_mutex_unlock(&philosopher->data->lock);
	pthread_mutex_unlock(philosopher->fork_left);
	pthread_mutex_unlock(philosopher->fork_right);
	pthread_mutex_lock(&philosopher->data->lock);
	if (philosopher->eat_count >= philosopher->data->num_must_eat)
	{	
		philosopher->reached_must_eat = true;
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	philosopher->data->all_philos_have_eaten = check_all_philos_have_eaten(philosopher->data);
	if (philosopher->data->all_philos_have_eaten == true)
	{
		philosopher->data->running = false;
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	if (philosopher->data->running == false || check_if_philo_is_dead(philosopher, false) == true)
	{
		philosopher->data->running = false;
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	pthread_mutex_unlock(&philosopher->data->lock);
	print_state(philosopher, "is sleeping");
	ft_usleep(philosopher->data->time_to_sleep, -42); // data race? se calhar adicionar, na philo struct um time_to_sleep
	print_state(philosopher, "is thinking");
	check_if_philo_is_dead(philosopher, false);
	pthread_mutex_lock(&philosopher->data->lock);
	if (philosopher->data->running == false || check_if_philo_is_dead(philosopher, false) == true)
	{
		philosopher->data->running = false;
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	if (philosopher->data->reached_must_eat == true)
	{
		pthread_mutex_unlock(&philosopher->data->lock);
		return ;
	}
	pthread_mutex_unlock(&philosopher->data->lock);
	return ;
}

static bool	check_all_philos_have_eaten(t_philo_data *data)
{
	unsigned int	i;
	bool			all_eaten;

	pthread_mutex_lock(&data->philo_eaten);
	i = 0;
	all_eaten = true;
	while (i < data->num_of_philos)
	{
		if (data->philosophers[i]->eat_count < data->num_must_eat)
		{
			all_eaten = false;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&data->philo_eaten);
	return (all_eaten);
}

static bool check_if_philo_is_dead(t_philo *philosopher, bool with_forks)
{
	uint64_t time_since_last_meal;

	if (!philosopher || !philosopher->data)
	{
		printf("Error: Invalid philosopher or data pointer\n");
		return true;
	}
	pthread_mutex_lock(&philosopher->data->philo_dead);
	time_since_last_meal = get_time() - philosopher->time_last_eat;
	if (time_since_last_meal > philosopher->data->time_to_die)
	{
		philosopher->dead = true;
		print_state(philosopher, "died");
		philosopher->data->running = false;
		if (with_forks)
		{
			pthread_mutex_unlock(philosopher->fork_left);
			if (philosopher->fork_right)
				pthread_mutex_unlock(philosopher->fork_right);
		}
		pthread_mutex_unlock(&philosopher->data->philo_dead);
		return true;
	}
	pthread_mutex_unlock(&philosopher->data->philo_dead);
	return false;
}

/* static void ft_changer(pthread_mutex_t ola, bool *runing, bool check)
{
	pthread_mutex_lock(&ola);
	*runing = check;
	pthread_mutex_unlock(&ola);
} */

//static void ft_checker(pthread_mutex_t ola, bool *runing, bool check)