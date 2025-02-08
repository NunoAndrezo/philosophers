/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:57 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/08 14:50:36 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

uint64_t	get_time_micro(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)time.tv_sec * 1000000 + time.tv_usec);
}

uint64_t	get_time(void)
{
	return (get_time_micro() / 1000);
}

bool	ft_usleep(unsigned long long micro_sec)
{
	uint64_t	start;
	uint64_t	end;

	start = get_time_micro();
	while (1)
	{
		end = get_time_micro();
		if (end - start >= micro_sec)
			return (true);
	}
	return (false);
}
