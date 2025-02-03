/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/02/03 21:36:34 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int arc, char **arv)
{
	t_philo_data	*data;
	t_philo		*philosophers;

	if ( arc == 5 || arc == 6)
	{
		if (is_args_good(arv) == 0)
		{
			write(2, "Error: Arguments are wrong\n", 27); //exemplo maximo numero de 200 philos
			exit (EXIT_FAILURE);
		}
		data = initiate_data();
		get_arg(data, arc, arv);
		creating_philos(data);
		//correr o programa
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	return (0);
}
