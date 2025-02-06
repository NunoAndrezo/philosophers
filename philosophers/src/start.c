/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:46:39 by nneves-a          #+#    #+#             */
/*   Updated: 2025/02/06 20:08:14 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start(t_philo_data *data)
{
	create_forks(data);
	data->start_time = get_time();
	data->running = true;
	
}