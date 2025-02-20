/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:36:23 by nneves-a          #+#    #+#             */
/*   Updated: 2024/04/22 18:57:44 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(dst) >= size || size == 0)
		return (ft_strlen(src) + size);
	while (dst[i] != '\0' && i < size)
		i++;
	while (src[j] != '\0' && (i + 1 + j) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
int	main(void)
{
    char dst[15] = "r";
    const char *src = "lorem ipsum dolor sit amet";
    size_t size = 5;

    size_t result = ft_strlcat(dst, src, size);

    printf("Concatenated string: %s\n", dst);
    printf("Total length after concatenation: %zu\n", result);

    return (0);
}
*/