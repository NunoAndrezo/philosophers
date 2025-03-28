/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:36:33 by nuno              #+#    #+#             */
/*   Updated: 2025/03/28 21:43:30 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	wait_all_threads(t_table *table)
{
	while (check_bool(&table->table_mutex, &table->philos_are_ready) == false)
		continue ;
}