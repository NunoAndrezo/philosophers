/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/04/21 15:03:47 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	is_args_good(char **arv, int arc);
static bool	check_len(char *s);

int	main(int arc, char **arv)
{
	t_table	*table;

	if (arc == 5 || arc == 6)
	{
		if (is_args_good(arv, arc) == false)
			error_and_exit("Arguments are wrong");
		table = ft_calloc(1, sizeof(t_table));
		if (!table)
			error_and_exit(RED "Error: Malloc failed" RESET);
		get_arg(table, arc, arv);
		initiate(table);
		start(table);
		vileda(table);
	}
	else
		error_and_exit(RED "Invalid number of arguments\n"
			RESET GREEN "Correct is ex: ./philo 5 800 200 200 [7]" RESET);
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
			error_and_exit("INT_MAX is the limit");
		j = 0;
		while (arv[i][j] == ' ')
			j++;
		while (arv[i][j])
		{
			if ((arv[i][j] < '0' || arv[i][j] > '9') && arv[i][j] != '+')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	check_len(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	if (i > 10)
		return (false);
	return (true);
}
