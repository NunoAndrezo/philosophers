/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:14:57 by nuno              #+#    #+#             */
/*   Updated: 2025/03/20 19:20:39 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *s)
{
	long	signal;
	long	res;
	long	i;

	if (!s || !s[0])
		return (0);
	signal = 1;
	res = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signal = -1;
		i++;
	}
	while(s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res = res * 10;
			res = s[i] - '0';
		}
		else
			exit(1);
		i++;	
	}
	return (res * signal);
}

