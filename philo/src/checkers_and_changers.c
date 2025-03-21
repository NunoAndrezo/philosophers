/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_and_changers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:29:51 by nuno              #+#    #+#             */
/*   Updated: 2025/03/21 15:33:12 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	change_bool(t_mutex *mutex, bool *var, bool value)
{
	mutex_handle(mutex, LOCK);
	*var = value;
	mutex_handle(mutex, UNLOCK);
}

bool	check_bool(t_mutex *mutex, bool *var)
{
	bool	ret;

	mutex_handle(mutex, LOCK);
	ret = *var;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	change_long(t_mutex *mutex, long *var, long value)
{
	mutex_handle(mutex, LOCK);
	*var = value;
	mutex_handle(mutex, UNLOCK);
}

bool	check_long(t_mutex *mutex, long *var)
{
	long	ret;

	mutex_handle(mutex, LOCK);
	ret = *var;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	simulation_is_running(t_table *table)
{
	return (check_bool(&table->table_mutex, &table->running));
}