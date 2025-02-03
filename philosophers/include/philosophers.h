/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:10:37 by nuno              #+#    #+#             */
/*   Updated: 2025/02/03 21:36:33 by nneves-a         ###   ########.fr       */
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


typedef struct s_state
{
	bool	awake;
	bool	full;
	bool	smart;
	bool	dead;
}		t_state;

typedef struct	s_philo
{
	int			id;
	int			eat_count;
	t_state		state;
	uint64_t	last_eat; //usigned long long
	pthread_t	philo_thread;
	t_philo		*next;
	t_philo		*prev;
}		t_philo;

typedef struct	s_philo_data
{
	unsigned int	num_of_philos;
	unsigned int	num_of_forks;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		start_time;
	unsigned int	num_must_eat;
	pthread_mutex_t	**forks;
	t_philo			**philosophers;
}		t_philo_data;

//initiate.c
void			get_arg(t_philo_data *data, int arc, char **arv);
t_philo_data	*initiate_data(void);
t_philo			*initate_philos(int n, t_philo_data *data);

//main_helper.c
void			get_arg(t_philo_data *data, int arc, char **arv);
t_philo_data	*initiate_data(void);

// time.c
uint64_t		get_time_micro(void);
uint64_t		get_time(void);
bool			ft_usleep(unsigned long long micro_sec);

#endif