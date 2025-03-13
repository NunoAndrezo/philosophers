/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/03/13 18:53:59 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	is_args_good(char **arv, int arc);

int	main(int arc, char **arv)
{
	t_philo_data	*data;

	if ( arc == 5 || arc == 6)
	{
		if (is_args_good(arv, arc) == 0)
		{
			write(2, "Error: Arguments are wrong\n", 27); //exemplo maximo numero de 200 philos
			exit (EXIT_FAILURE);
		}
		data = initiate_data();
		get_arg(data, arc, arv);
		creating_philos(data);
		start(data);
		destroy_forks(data);
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
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