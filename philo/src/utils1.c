/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_and_changers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:29:51 by nuno              #+#    #+#             */
/*   Updated: 2025/05/07 22:43:08 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

long	check_long(t_mutex *mutex, long *var)
{
	long	ret;

	mutex_handle(mutex, LOCK);
	ret = *var;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increase_long(t_mutex *mutex, long *var)
{
	mutex_handle(mutex, LOCK);
	(*var)++;
	mutex_handle(mutex, UNLOCK);
}

void	decrease_long(t_mutex *mutex, long *var)
{
	mutex_handle(mutex, LOCK);
	(*var)--;
	mutex_handle(mutex, UNLOCK);
}
