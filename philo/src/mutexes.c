/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:00 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/20 21:00:23 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	handle_mutex_return(int	ret_val, t_mutex_code code)
{
	if (ret_val == 0)
		return ;
	if (EINVAL == ret_val && (code == LOCK || code == UNLOCK))
		error_and_exit(RED"The value specified by mutex is invalid"RESET);
	else if (EINVAL == ret_val && code == INIT)
		error_and_exit(RED"The value specified by attr is invalid"RESET);
	else if (EDEADLK == ret_val)
		error_and_exit(RED"Deadlock would occur if the thread blocked was waiting for a mutex"RESET);
	else if (EPERM == ret_val)
		error_and_exit(RED"The current thread does not hold a lock on mutex"RESET);
	else if (ENOMEM == ret_val)
		error_and_exit(RED"The process cannot allocate enough memory to create another mutex"RESET);
	else if (EBUSY == ret_val)
		error_and_exit(RED"The mutex is already locked"RESET);
	
}

void	mutex_handle(t_mutex *mutex, t_mutex_code code)
{
	if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		error_and_exit(RED"Wrong mutex code"RESET);
}

void	print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->table->print_state);
	printf("%lu %d %s\n", get_time() - philo->table->start_time, philo->id, str);
	pthread_mutex_unlock(philo->table->print_state);
}