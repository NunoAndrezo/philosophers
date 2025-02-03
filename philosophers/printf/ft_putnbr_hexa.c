/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:36:43 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/07 20:01:41 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hexa(unsigned int n, int x)
{
	int				count;
	char			*sym;
	char			*symup;

	sym = "0123456789abcdef";
	symup = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hexa(n / 16, x);
		count += ft_putnbr_hexa(n % 16, x);
	}
	else
	{
		if (x == 1)
			count += ft_print_char(sym[n % 16]);
		else
			count += ft_print_char(symup[n % 16]);
	}
	return (count);
}
