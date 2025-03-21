#include "../include/philosophers.h"

static void wait_for_all_philos(t_table *table);

void	*routine(void *table)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)table;
	wait_for_all_philos(philosopher->table);
}

static void wait_for_all_philos(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philosophers[i].philo_thread, NULL);
}