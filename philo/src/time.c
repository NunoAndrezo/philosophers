/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:57 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/29 02:01:46 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

uint64_t	get_time(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_and_exit("gettimeofday failed\n");
	if (SECONDS == time_code)
		return (time.tv_sec + (time.tv_usec / 1000000));
	else if (MILISECONDS == time_code)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else if (MICROSECONDS == time_code)
		return ((time.tv_sec * 1000000) + time.tv_usec);
	else
		return (error_and_exit("Wrong time_code"), 2222);
}

void	ft_usleep(unsigned long long micro_sec, t_table	*table)
{
	uint64_t	start;
	uint64_t	elapsed;
	uint64_t	rem;

	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < micro_sec)
	{
		if (check_bool(&table->table_mutex, &table->running) == false)
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		rem = micro_sec - elapsed;
		if (rem > 1000)
			usleep(micro_sec / 2);
		else
		{
			while (get_time(MICROSECONDS) - start < micro_sec)
				continue ;
		}
	}
}
