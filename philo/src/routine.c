#include "../include/philosophers.h"

static void	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);
static void	ft_think(t_philo *philo);
static void wait_for_all_philos(t_table *table);

void	*routine(void *table)
{
	t_philo	*philo;

	philo = (t_philo *)table;
	//spinlock:
	wait_for_all_philos(philo->table);

	// set last meal time
	while (simulation_is_running(table) == true)
	{
		if (check_bool(&philo->table->table_mutex, &philo->full))
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}

	return (NULL);
}

static void	ft_eat(t_philo *philo)
{
	mutex_handle(&philo->first_fork->fork, LOCK);
	print_mutex(philo, FIRST_FORK);
	mutex_handle(&philo->second_fork->fork, LOCK);
	print_mutex(philo, SECOND_FORK);

	change_long(&philo->philo_mutex, &philo->time_last_eat, get_time(MILISECONDS));
	philo->eat_count++;
	print_mutex(philo, EATING);
	ft_usleep(philo->table->time_to_eat, philo->table);
	mutex_handle(&philo->table->checker, LOCK);
	if (philo->table->nr_meals_limit > 0 && philo->eat_count == philo->table->nr_meals_limit)
	{
		change_bool(&philo->table->table_mutex, &philo->full, true);
		mutex_handle(&philo->table->checker, UNLOCK);
		return ;
	}
	mutex_handle(&philo->table->checker, UNLOCK);
	mutex_handle(&philo->first_fork->fork, UNLOCK);
	mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	ft_sleep(t_philo *philo)
{
	print_mutex(philo, SLEEPING);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

static void	ft_think(t_philo *philo)
{
	print_mutex(philo, THINKING);
}

static void wait_for_all_philos(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philosophers[i].philo_thread, NULL);
}