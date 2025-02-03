/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:10:27 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/07 19:10:24 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str == NULL)
	{
		return (count += ft_print_str("(null)"));
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		count++;
		i++;
	}
	return (count);
}
