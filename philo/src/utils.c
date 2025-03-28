/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:55:18 by nuno              #+#    #+#             */
/*   Updated: 2025/03/28 21:45:12 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	error_and_exit(const char *str)
{
	printf(RED"Error %s\n"RESET, str);
	exit(1);
}

long	ft_atol(char *s)
{
	long	signal;
	long	res;
	long	i;

	if (!s || !s[0])
		return (0);
	signal = 1;
	res = 0;
	i = 0;
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
			error_and_exit(RED"ERROR: Invalid Arguments"RESET);
		i++;	
	}
	return (res * signal);
}

/* adicionar ao makefile a de cima.

adicionar ao libft:

ft_matrix_len(); */
