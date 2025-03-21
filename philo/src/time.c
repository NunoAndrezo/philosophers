/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:57 by nneves-a          #+#    #+#             */
/*   Updated: 2025/03/21 16:31:47 by nuno             ###   ########.fr       */
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

bool	ft_usleep(unsigned long long micro_sec, uint64_t flag)
{
	uint64_t	start;
	uint64_t	end;


	if ((long long)flag < 0)
	{
		start = get_time_micro();
		while (1)
		{
			end = get_time_micro();
			if (end - start >= micro_sec)
				return (true);
		}
	}
	else
	{

		start = get_time_micro();
		while (flag - start > 0)
		{
			end = get_time_micro();
			if (end - start >= micro_sec)
				return (false);
		}
	}
	return (false);
}
