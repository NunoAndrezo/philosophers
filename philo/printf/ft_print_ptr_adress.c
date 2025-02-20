/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_adress.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:36:37 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/09 21:49:07 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put_char(int c)
{
	int				count;
	unsigned char	a;

	a = (unsigned char)c;
	count = 0;
	write(1, &a, 1);
	count++;
	return (count);
}

static int	ft_print_ptr_adress_helper(unsigned long a)
{
	int		count;
	char	*sym;

	count = 0;
	sym = "0123456789abcdef";
	if (a >= 16)
	{
		count += ft_print_ptr_adress_helper(a / 16);
		count += ft_print_ptr_adress_helper(a % 16);
	}
	else
		count += ft_put_char(sym[a % 16]);
	return (count);
}

int	ft_print_ptr_adress(void *ptr)
{
	int				count;
	unsigned long	a;

	count = 0;
	a = (unsigned long)ptr;
	if (!ptr)
	{
		return (count += ft_print_str("(nil)"));
	}
	count += write(1, "0x", 2);
	count += ft_print_ptr_adress_helper(a);
	return (count);
}
