#include "../include/philosophers.h"

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
		if (check_bool(&philo->table->table_mutex, philo->full))
			break ;
		eat(philo);
		sleep(philo);
		think(philo);
	}

	return (NULL);
}

static void wait_for_all_philos(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philosophers[i].philo_thread, NULL);
}