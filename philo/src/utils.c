/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:55:18 by nuno              #+#    #+#             */
/*   Updated: 2025/05/05 00:56:52 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_atol_helper(char *s, long *i);

void	error_and_exit(const char *str)
{
	printf(RED "Error: %s\n" RESET, str);
	exit(1);
}

long	ft_atol(char *s)
{
	long	signal;
	long	r;
	long	i;

	i = 0;
	r = 0;
	if (!s || !s[0])
		error_and_exit("Invalid Arguments in ft_atol");
	while (s[i] == ' ')
		i++;
	signal = ft_atol_helper(s, &i);
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			r *= 10;
			r += s[i++] - '0';
		}
		else
			error_and_exit("Invalid Arguments");
	}
	if (r > LONG_MAX / 10
		|| (r == LONG_MAX / 10 && (s[i] - '0') > LONG_MAX % 10))
		error_and_exit("Number out of range");
	return (r * signal);
}

static int	ft_atol_helper(char *s, long *i)
{
	int		signal;
	long	j;

	j = *i;
	signal = 1;
	if (s[j] == '-' || s[j] == '+')
	{
		if (s[j] == '-')
			signal = -1;
		j++;
	}
	*i = j;
	return (signal);
}

void	vileda(t_table *table)
{
	(void)table;
 	int	i;

	i = -1;
	if (!table)
		return ;
	if (table->philosophers)
	{
			while (++i < table->num_of_philos)
				pthread_mutex_destroy(&table->forks[i].fork);
			free(table->philosophers);
			table->philosophers = NULL;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->table_mutex);
	}
	free(table);
	table = NULL; 
}