/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:58 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/09 22:32:44 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(const char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		count += ft_print_ptr_adress(va_arg(ap, void *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_putnbr(va_arg(ap, int));
	else if (specifier == 'u')
		count += ft_putnbr_unsigned(va_arg(ap, unsigned int));
	else if (specifier == 'x')
		count += ft_putnbr_hexa(va_arg(ap, long), 1);
	else if (specifier == 'X')
		count += ft_putnbr_hexa(va_arg(ap, long), 2);
	else if (specifier == '%')
		count += write(1, "%", 1);
	return (count);
}
