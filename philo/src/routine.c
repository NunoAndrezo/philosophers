#include "../include/philosophers.h"

static void	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);
static void	ft_think(t_philo *philo, bool did_routine_start);
static void	make_a_mf_wait(t_philo *philo);

void	*routine(void *philoso)
{
	t_philo	*philo;

	philo = (t_philo *)philoso;
	while (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
		usleep(100);
	change_long(&philo->philo_mutex, &philo->time_last_eat, get_time(MILISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->num_threads_running);
	
	make_a_mf_wait(philo);
	while (check_bool(&philo->table->table_mutex, &philo->table->running) == true)
	{
		if (check_bool(&philo->philo_mutex, &philo->full) == true)
			return (NULL);
		if (check_bool(&philo->philo_mutex, &philo->dead) == true)
		{
			print_mutex(philo, DEAD);
			return (NULL);
		}
		ft_eat(philo);
		ft_sleep(philo);
		if (check_bool(&philo->philo_mutex, &philo->full) == true)
			return (NULL);
		if (check_bool(&philo->philo_mutex, &philo->dead) == true)
		{
			print_mutex(philo, DEAD);
			return (NULL);
		}
		ft_think(philo, true);
	}
	return (NULL);
}

static void	ft_eat(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	print_mutex(philo, FIRST_FORK);
	mutex_handle(&philo->right_fork->fork, LOCK);
	print_mutex(philo, SECOND_FORK);

	change_long(&philo->philo_mutex, &philo->time_last_eat, get_time(MILISECONDS));
	philo->eat_count++;
	print_mutex(philo, EATING);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (check_long(&philo->table->table_mutex, &philo->table->nr_meals_limit) > 0 && check_long(&philo->philo_mutex, &philo->eat_count) == philo->table->nr_meals_limit)
		change_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}

static void	ft_sleep(t_philo *philo)
{
	print_mutex(philo, SLEEPING);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

static void	ft_think(t_philo *philo, bool did_routine_start)
{
	long	t_to_sleep;
	long	t_to_eat;
	long	t_to_think;

	if (did_routine_start == true)
		print_mutex(philo, THINKING);
	if (philo->table->num_of_philos % 2 == 0)
		return ;
	printf("philos are not even, so we need to think a bit more\n");
	t_to_sleep = philo->table->time_to_sleep;
	t_to_eat = philo->table->time_to_eat;
	t_to_think = ((t_to_eat * 2) - t_to_sleep);
	if (t_to_think < 0)
		t_to_think = 0;
	ft_usleep((t_to_think * 0.42), philo->table);
}

static void	make_a_mf_wait(t_philo *philo)
{
	if (philo->table->num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
				ft_usleep(30000, philo->table); // 30miliseconds, half the minimum 60mili
	}
	else
	{
		if (philo->id % 2 != 0)
			ft_think(philo, false);
	}
}