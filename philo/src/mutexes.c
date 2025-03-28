/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:00 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/28 21:37:21 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* static void	handle_mutex_return(int	ret_val, t_mutex_code code)
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
	
} */

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

void	print_mutex(t_philo *philo, t_print_status status)
{
	uint64_t print_time;

	if (philo->full) // thread safe?
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	print_time = get_time(MILISECONDS) - philo->table->start_time;
	if ((FIRST_FORK == status|| SECOND_FORK == status) && simulation_is_running(philo->table) == true)
			printf(BLUE"%ld"RESET"%ld has taken a fork\n", print_time, philo->id);
	else if (status == EATING && simulation_is_running(philo->table) == 1)
			printf(YELLOW"%ld"RESET"%ld is eating\n", print_time, philo->id);
	else if (status == SLEEPING && simulation_is_running(philo->table))
			printf(MAGENTA"%ld"RESET"%ld is sleeping\n", print_time, philo->id);
	else if (status == THINKING && simulation_is_running(philo->table) == 1)
			printf(CYAN"%ld"RESET"%ld is thinking\n", print_time, philo->id);
	else if (status == DEAD)
			printf(RED"%ld"RESET"%ld died\n", print_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
