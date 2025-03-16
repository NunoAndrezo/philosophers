/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/03/16 02:06:18 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	is_args_good(char **arv, int arc);

int	main(int arc, char **arv)
{
	t_philo_data	*data;

	if ( arc == 5 || arc == 6)
	{
		if (is_args_good(arv, arc) == false)
		{
			write(2, "Error: Arguments are wrong\n", 27); //exemplo maximo numero de 200 philos
			exit (EXIT_FAILURE); // can i use exit(); ??
		}
		data = initiate_data();
		get_arg(data, arc, arv);
		creating_philos(data);
		start(data);
		destroy_forks(data);
	}
	else
	{
		error_and_exit("Invalid number of arguments"GREEN"Correct is ex: ./philo 5 800 200 200 [5]\n"RESET);
		return (1);
	}
	return (0);
}

static bool	is_args_good(char **arv, int arc)
{
	int	i;
	int	j;

	i = 1;
	while (i < arc)
	{
		j = 0;
		while (arv[i][j])
		{
			if (arv[i][j] < '0' || arv[i][j] > '9')
			{
				if (arv[i][j] == '-' || arv[i][j] == '+')
					continue ;
				else
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}