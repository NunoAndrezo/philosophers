/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:57 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/03 13:15:02 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_and_exit("gettimeofday failed\n");
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
