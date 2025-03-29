/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/03/29 11:35:29 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	is_args_good(char **arv, int arc);
static bool	check_len(char *s);
/* static void print_table(t_table *table);
static void	print_philosophers(t_table *table); */

int	main(int arc, char **arv)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		error_and_exit(RED"Error: Malloc failed"RESET);
	if ( arc == 5 || arc == 6)
	{
		if (is_args_good(arv, arc) == false)
			error_and_exit("Arguments are wrong\n");
		get_arg(table, arc, arv);
		initiate(table);
		//print_table(table);
		//print_philosophers(table);
		start(table);
		// clean_everything() // destroy_forks(&table); etcS
	}
	else
		error_and_exit(RED"Invalid number of arguments"RESET GREEN"Correct is ex: ./philo 5 800 200 200 [5]\n"RESET);
	return (0);
}

/* static void	print_philosophers(t_table *table)
{
	int	i;
	i = -1;
	while (++i < table->num_of_philos)
	{
		printf("Philosopher %d\n", i + 1);
		printf("Philosopher %d id: %ld\n", i + 1, table->philosophers[i].id);
		printf("Philosopher %d eat count: %ld\n", i + 1, table->philosophers[i].eat_count);
		printf("Philosopher %d full: %d\n", i + 1, table->philosophers[i].full);
		printf("Philosopher %d dead: %d\n", i + 1, table->philosophers[i].dead);
		printf("Philosopher %d time last eat: %ld\n", i + 1, table->philosophers[i].time_last_eat);
		printf("Philosopher %d philo_thread: %p\n", i + 1, &table->philosophers[i].philo_thread);
		printf("Philosopher %d left fork: %p\n", i + 1, table->philosophers[i].left_fork);
		printf("Philosopher %d right fork: %p\n", i + 1, table->philosophers[i].right_fork);
		printf("Philosopher %d table: %p\n", i + 1, table->philosophers[i].table);
		printf("Philosopher %d philo_mutex: %p\n", i + 1, &table->philosophers[i].philo_mutex);
		printf("Philospher pointer: %p\n", &table->philosophers[i]);
	}
}

static void print_table(t_table *table)
{
	printf("num_of_philos: %ld\n", table->num_of_philos);
	printf("num_of_forks: %ld\n", table->num_of_forks);
	printf("time_to_die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time_to_sleep: %ld\n", table->time_to_sleep);
	printf("nr_meals_limit: %ld\n", table->nr_meals_limit);
	printf("start_time: %ld\n", table->start_time);
	printf("philos_are_ready: %d\n", table->philos_are_ready);
	printf("running: %d\n", table->running);
	printf("philosophers: %p\n", table->philosophers);
	printf("forks: %p\n", table->forks);
	printf("print_mutex: %p\n", &table->print_mutex);
	printf("table_mutex: %p\n", &table->table_mutex);
	printf("table: %p\n", table);
} */

static bool	is_args_good(char **arv, int arc)
{
	int	i;
	int	j;

	i = 1;
	while (i < arc)
	{
		if (check_len(arv[i]) == false)
			error_and_exit("INT_MAX is the limit");
		j = 0;
		while (arv[i][j] == ' ')
			j++;
		while (arv[i][j])
		{
			if ((arv[i][j] < '0' || arv[i][j] > '9') && arv[i][j] != '+')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	check_len(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	if (i > 10)
		return (false);
	return (true);
}