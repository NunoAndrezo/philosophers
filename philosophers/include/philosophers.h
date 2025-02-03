/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:10:37 by nuno              #+#    #+#             */
/*   Updated: 2025/01/30 00:09:11 by nuno             ###   ########.fr       */
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
# include <sys/types.h>s
# include <stdbool.h>
# include <stdint.h>

typedef enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}		t_state;

typedef struct	s_philo
{
	int			id;
	int			eat_count;
	uint64_t		last_eat; //usigned long long
	pthread_t		philo_thread;
	t_state		state;
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
	unsigned int	num_must_eat;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	t_philo		*philosopher;
}		t_philo_data;

//main_helper.c
void	get_arg(t_philo_data *data, int arc, char **arv);
t_philo_data	*initiate_data(void);


#endif