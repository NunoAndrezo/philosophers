/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:10:37 by nuno              #+#    #+#             */
/*   Updated: 2025/03/18 21:19:53 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHERS_H
#  define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"

#define RESET   "\x1b[0m"
#define BLACK   "\x1b[1;30m"
#define RED     "\x1b[1;31m"
#define GREEN   "\x1b[1;32m"
#define YELLOW  "\x1b[1;33m"
#define BLUE    "\x1b[1;34m"
#define MAGENTA "\x1b[1;35m"
#define CYAN    "\x1b[1;36m"
#define WHITE   "\x1b[1;37m"

typedef struct	s_table t_table;
typedef pthread_mutex_t t_mutex;

typedef struct	s_fork
{
	long		fork_id;
	t_mutex		fork;
}		t_fork;

typedef struct	s_philo
{
	long			id;
	long			eat_count;
	bool			have_not_eaten;
	bool			dead;
	long			time_last_eat; //usigned long long
	pthread_t		philo_thread;
	t_fork			*fork_left;
	t_fork			*fork_right;
	t_table			*table;
}		t_philo;

struct	s_table
{
	long	num_of_philos;
	long	num_of_forks;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nr_of_meals_to_eat;
	
	long	start_time;
	bool	running; // false if a philo dies or all philos are full
	bool	all_philos_full;
	
	t_philo	**philosophers;
	t_mutex	**forks;
	t_mutex	*print_state;
	t_mutex	lock;
	t_mutex	check_mtx;
	t_mutex	helper;
	t_mutex	philo_eaten;
	t_mutex	philo_dead;
};

//main.c
//int	main(int arc, char **arv);

//initiate.c
void		get_arg(t_table *table, int arc, char **arv);
t_table		*initiate_data(void);
void		initiate_philosopher(int n, t_philo *philosopher, t_table *table);

// time.c
uint64_t		get_time_micro(void);
uint64_t		get_time(void);
bool			ft_usleep(unsigned long long micro_sec, uint64_t flag);

// creating_philos.c
void	creating_philos(t_table *table);

//routine.c
void	*routine(void *philo);

//mutexes.c
void	create_forks_mutex(t_table *table);
void	destroy_forks(t_table *table);
void	create_print_mutex(t_table *table);
void	print_state(t_philo *philo, char *str);

//start.c
void	start(t_table *table);

//utils.c
void	error_and_exit(const char *str);

#endif with big ass