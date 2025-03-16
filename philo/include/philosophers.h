/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:10:37 by nuno              #+#    #+#             */
/*   Updated: 2025/03/16 02:06:38 by nuno             ###   ########.fr       */
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

typedef struct	s_philo_data t_philo_data;
typedef pthread_mutex_t t_mutex;

typedef struct	s_fork
{
	long		fork_id;
	t_mutex	fork;
}		t_fork;

typedef struct	s_philo
{
	unsigned int		id;
	int				eat_count;
	bool				have_not_eaten;
	bool				dead;
	uint64_t			time_last_eat; //usigned long long
	pthread_t			philo_thread;
	t_fork			*fork_left;
	t_fork			*fork_right;
	t_philo_data		*data;
}		t_philo;

struct	s_philo_data
{
	unsigned int	num_of_philos;
	unsigned int	num_of_forks;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int			num_must_eat;
	uint64_t		start_time;
	bool			running;
	bool			all_philos_have_eaten;

	t_philo		**philosophers;
	t_mutex		**forks;
	t_mutex		*print_state;
	t_mutex		lock;
	t_mutex		check_mtx;
	t_mutex		helper;
	t_mutex		philo_eaten;
	t_mutex		philo_dead;
};

//main.c
//int	main(int arc, char **arv);

//initiate.c
void			get_arg(t_philo_data *data, int arc, char **arv);
t_philo_data	*initiate_data(void);
void		initiate_philosopher(int n, t_philo *philosopher, t_philo_data *data);

// time.c
uint64_t		get_time_micro(void);
uint64_t		get_time(void);
bool			ft_usleep(unsigned long long micro_sec, uint64_t flag);

// creating_philos.c
void	creating_philos(t_philo_data *data);

//routine.c
void	*routine(void *philo);

//mutexes.c
void	create_forks_mutex(t_philo_data *data);
void	destroy_forks(t_philo_data *data);
void	create_print_mutex(t_philo_data *data);
void	print_state(t_philo *philo, char *str);

//start.c
void	start(t_philo_data *data);

//utils.c
void	error_and_exit(const char *str);

#endif