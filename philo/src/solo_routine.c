/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:03:14 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/07 23:06:24 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*solo_routine(t_philo *philo)
{
	while (check_bool(&philo->table->table_mutex,
			&philo->table->running) == false)
		usleep(100);
	print_mutex(philo, FIRST_FORK);
	usleep_with_checker(philo->table->time_to_die, philo);
	print_mutex(philo, DEAD);
	change_bool(&philo->table->table_mutex, &philo->table->running, false);
	return (NULL);
}
