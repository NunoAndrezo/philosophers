/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:36:57 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/09 22:34:54 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_print_char(int c);
int	ft_putnbr(int n);
int	ft_putnbr_hexa(unsigned int n, int x);
int	ft_print_ptr_adress(void *ptr);
int	ft_printf(const char *format, ...);
int	ft_print_format(const char specifier, va_list ap);
int	ft_print_str(char *str);
int	ft_putnbr_unsigned(unsigned int n);

#endif
