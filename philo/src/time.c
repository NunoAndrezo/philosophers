/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:57 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/12 00:51:39 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (ft_error("gettimeofday failed\n"));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long time_to_wait)
{
	long	current_time;

	current_time = get_time();
	while (get_time() - current_time < time_to_wait)
		continue ;
}

long	get_current_time(long current)
{
	return (get_time() - current);
}

void	usleep_with_checker(long time, t_philo *philo)
{
	long	start;
	long	current;

	if (philo->full == true)
		return ;
	start = get_current_time(philo->table->start_time);
	while (1)
	{
		current = get_current_time(philo->table->start_time);
		if (philo_died(philo) == true)
			break ;
		if (current - start >= time)
			break ;
		usleep(60);
	}
}
