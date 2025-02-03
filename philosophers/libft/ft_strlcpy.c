/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:52:22 by nneves-a          #+#    #+#             */
/*   Updated: 2024/04/17 16:47:27 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	x;
	size_t	srclen;

	x = 0;
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (src[x] != '\0' && (x + 1) < size)
	{
		dest[x] = src[x];
		x++;
	}
	if (size > 0)
		dest[x] = '\0';
	return (srclen);
}
