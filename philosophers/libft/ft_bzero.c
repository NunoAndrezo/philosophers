/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:19:27 by nneves-a          #+#    #+#             */
/*   Updated: 2024/04/18 22:50:14 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}
/*
int	main(void)
{
	char	x[] = "Moto Ratos de Marte";
	char	y[] = "Moto Ratos de Marte";
	bzero(x, 12);
	printf("%c\n", x[11]);
	ft_bzero(y, 12);
	printf("%c\n", y[11]);
	return (0);
}
*/
