/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:40:33 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/09 21:47:32 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int			i;
	int			count;
	va_list		ap;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			count = count + ft_print_format(format[i], ap);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
/*
int main(void)
{
	int count;

	count = ft_printf("%p %p", 0, 0);
	ft_printf("\nThe number of chars that have been read are/is: %d\n", count);
	count = 0;
	count = printf("%p %p", 0, 0);
	printf("\nThe number of chars that have been read are/is: %d\n", count);
	return (0);
} */
