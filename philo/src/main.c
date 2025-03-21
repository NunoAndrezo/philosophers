/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/03/21 15:15:27 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	is_args_good(char **arv, int arc);
static bool	check_len(char *s);

int	main(int arc, char **arv)
{
	t_table	table;

	if ( arc == 5 || arc == 6)
	{
		if (is_args_good(arv, arc) == false)
			error_and_exit("Error: Arguments are wrong\n");
		get_arg(&table, arc, arv);
		initiate(&table);
		start(&table);
		// clean_everything() // destroy_forks(&table); etcS
	}
	else
		error_and_exit(RED"Invalid number of arguments"RESET GREEN"Correct is ex: ./philo 5 800 200 200 [5]\n"RESET);
	return (0);
}

static bool	is_args_good(char **arv, int arc)
{
	int	i;
	int	j;

	i = 1;
	
	while (i < arc)
	{
		if (check_len(arv[i]) == false)
			error_and_exit("ERROR: INT_MAX is the limit");
		j = 0;
		while (arv[i][j] == ' ')
			j++;
		while (arv[i][j])
		{
			if ((arv[i][j] > '0' && arv[i][j] < '9') || arv[i][j] == '+')
				continue ;
			else
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	check_len(char *s)
{
	int	i;

	i = ft_len(s);
	if (i > 10)
		return (false);
	return (true);
}