/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:05:25 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/09 17:09:56 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*str;

	i = 0;
	dst = (unsigned char *) dest;
	str = (unsigned char *) src;
	if (src < dest)
	{
		i = n;
		while (i > 0)
		{
			dst[i - 1] = str[i - 1];
			i--;
		}
		return (dst);
	}
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
    char str1[] = "";
    char buffer[20];

    printf("Before ft_memmove: %s\n", str1);

    ft_memmove(buffer, str1, 5); // Copy str1 to buffer
    printf("After ft_memmove: %s\n", buffer);

    return 0;
}
*/
