/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:10:37 by nuno              #+#    #+#             */
/*   Updated: 2025/02/17 17:06:50 by nneves-a         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "../printf/ft_printf.h"

typedef struct s_state
{
	bool	sleeping;
	bool	eating;
	bool	thinking;
	bool	dead;
}		t_state;

typedef struct	s_philo
{
	unsigned int		id;
	unsigned int		eat_count;
	t_state			state;
	uint64_t			time_last_eat; //usigned long long
	pthread_t			philo_thread;
	struct s_philo_data	*data;
}		t_philo;

typedef struct	s_philo_data
{
	bool			ready_to_start;
	bool			running;
	unsigned int	num_of_philos;
	unsigned int	num_of_forks;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		start_time;
	unsigned int	num_must_eat;
	pthread_mutex_t	**forks;
	t_philo			**philosophers;
	pthread_mutex_t	*print_state;
}		t_philo_data;

//main.c
//int	main(int arc, char **arv);

//initiate.c
void			get_arg(t_philo_data *data, int arc, char **arv);
void			initiate_data(t_philo_data *data);
t_philo			*initiate_philosopher(int n, t_philo *philosopher, t_philo_data *data);

// time.c
uint64_t		get_time_micro(void);
uint64_t		get_time(void);
bool			ft_usleep(unsigned long long micro_sec);

// creating_philos.c
void	creating_philos(t_philo_data *data);
void	join_threads(t_philo_data *data);

//routine.c
void	*routine(void *philo);
void	grabbing_forks(t_philo *philosopher);

//mutexes.c
void	create_forks(t_philo_data *data);
void	destroy_forks(t_philo_data *data);
void	create_print_mutex(t_philo_data *data);
void	print_state(t_philo *philo, char *str);

//start.c
void	start(t_philo_data *data);

#endif