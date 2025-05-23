/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:48:00 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/12 00:51:03 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	mutex_handle(t_mutex *mutex, t_mutex_code code)
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
		return (ft_error(RED "Wrong mutex code" RESET));
	return (0);
}

void	print_mutex(t_philo *philo, t_print_status status)
{
	long	print_time;

	if (philo->full == true)
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	if (check_bool(&philo->table->table_mutex, &philo->table->running) == false)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	print_time = get_current_time(philo->table->start_time);
	if ((FIRST_FORK == status || SECOND_FORK == status))
		printf(BLUE"%ld "RESET"%ld has taken a fork\n", print_time, philo->id);
	else if (status == EATING)
		printf(YELLOW"%ld "RESET"%ld is eating\n", print_time, philo->id);
	else if (status == SLEEPING)
		printf(MAGENTA"%ld "RESET"%ld is sleeping\n", print_time, philo->id);
	else if (status == THINKING)
		printf(CYAN "%ld " RESET "%ld is thinking\n", print_time, philo->id);
	else if (status == DEAD)
		printf(RED "%ld " RESET "%ld died\n", print_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
