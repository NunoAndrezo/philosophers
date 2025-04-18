/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:10:37 by nuno              #+#    #+#             */
/*   Updated: 2025/04/17 22:45:28 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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
# include <errno.h>

# define RESET		"\x1b[0m"
# define BLACK		"\x1b[1;30m"
# define RED		"\x1b[1;31m"
# define GREEN		"\x1b[1;32m"
# define YELLOW		"\x1b[1;33m"
# define BLUE		"\x1b[1;34m"
# define MAGENTA	"\x1b[1;35m"
# define CYAN		"\x1b[1;36m"
# define WHITE		"\x1b[1;37m"

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef enum e_print_status
{
	FIRST_FORK,
	SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
}	t_print_status;

typedef enum e_mutex_code
{
	INIT,
	LOCK,
	UNLOCK,
	CREATE,
	DESTROY,
	JOIN,
	DETACH,
}	t_mutex_code;

typedef struct s_fork
{
	long	id;
	t_mutex	fork;
}		t_fork;

typedef struct s_philo
{
	long		id;
	long		eat_count;
	bool		full;
	bool		dead;
	long		time_last_eat;
	pthread_t	philo_thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_table		*table;
	t_mutex		philo_mutex;
}		t_philo;

struct	s_table
{
	long		num_of_philos;
	long		num_of_forks;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nr_meals_limit;
	long		start_time;
	bool		running;
	bool		philos_are_ready;
	long		num_threads_running;
	t_philo		*philosophers;
	t_fork		*forks;
	pthread_t	monitor_thread;
	t_mutex		print_mutex;
	t_mutex		table_mutex;
};

//main.c
//int	main(int arc, char **arv);

//initiate.c
void			get_arg(t_table *table, int arc, char **arv);
void			initiate(t_table *table);

//checkers_and_changers.c
void			change_bool(t_mutex *mutex, bool *var, bool value);
bool			check_bool(t_mutex *mutex, bool *var);

void			change_long(t_mutex *mutex, long *var, long value);
long			check_long(t_mutex *mutex, long *var);
void			increase_long(t_mutex *mutex, long *var);

// time.c
long			get_time();
void			ft_usleep(long start);
long			get_current_time(long current);

//routine.c
void			*routine(void *philoso);

//routine2.c
void			arroz_de_cabidela(t_philo *philo);
void			ft_zzz(t_philo *philo);
void			thinking_alot(t_philo *philo);

//monitor_routine.c
void			*monitor_routine(void *table);

//mutexes.c
void			mutex_handle(t_mutex *mutex, t_mutex_code code);
void			print_mutex(t_philo *philo, t_print_status status);

//start.c
void			start(t_table *table);

//utils.c
void			error_and_exit(const char *str);
long			ft_atol(char *s);

//cleaners_and_frees.c
void			vileda(t_table *table);

#endif