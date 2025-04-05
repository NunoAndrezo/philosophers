/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:00 by nneves-a          #+#    #+#             */
/*   Updated: 2025/04/05 18:08:41 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	print_time = get_time(MILISECONDS) - philo->table->start_time;
	if ((FIRST_FORK == status|| SECOND_FORK == status) && check_bool(&philo->table->table_mutex, &philo->table->running))
			printf(BLUE"%ld "RESET"%ld has taken a fork\n", print_time, philo->id);
	else if (status == EATING && check_bool(&philo->table->table_mutex, &philo->table->running) == 1)
			printf(YELLOW"%ld "RESET"%ld is eating\n", print_time, philo->id);
	else if (status == SLEEPING && check_bool(&philo->table->table_mutex, &philo->table->running) == 1)
			printf(MAGENTA"%ld "RESET"%ld is sleeping\n", print_time, philo->id);
	else if (status == THINKING && check_bool(&philo->table->table_mutex, &philo->table->running) == 1)
			printf(CYAN"%ld "RESET"%ld is thinking\n", print_time, philo->id);
	else if (status == DEAD)
			printf(RED"%ld "RESET"%ld died\n", print_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
