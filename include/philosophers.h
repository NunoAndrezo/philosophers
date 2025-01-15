/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:10:37 by nuno              #+#    #+#             */
/*   Updated: 2025/01/13 21:35:10 by nuno             ###   ########.fr       */
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
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct	s_philo
{
	int num;
	bool	is_eating;
	bool	is_sleeping;
	bool	is_thinking;
	bool	is_dead;
	int	left_fork;
	int	right_fork;
	int	eat_count;
	long	last_eat;
	t_philo *next;
	t_philo *prev;
}		t_philo;

typedef struct	s_philo_data
{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_eat;
	bool is_dead;
	long start_time;

	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
}		t_philo_data;

#endif