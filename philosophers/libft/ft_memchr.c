/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:28 by nneves-a          #+#    #+#             */
/*   Updated: 2024/04/17 13:10:19 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (0);
}
/*
int     main(void)
{
	const char s1[] = "Moto Ratos";
	int c1 = 'R';
	const char s2[] = "Moto Ratos";
	int c2 = 'R';
	char *result1 = ft_memchr(s1, c1, 10);  // Find 'R' in s1 (first 10 bytes)

	if (result1 != NULL)
	{
        	*result1 = 'X';  // Replace first occurrence of 'R' with 'X'
        	printf("Modified s1: %s\n", s1);  // Print modified s1
    	}
    	else
    	{
        	printf("Character not found in s1\n");
    	}

    	char *result2 = memchr(s2, c2, 10);  // Find 'R' in s2 (first 10 bytes)
    	if (result2 != NULL)
    	{
        	*result2 = 'Y';  // Replace first occurrence of 'R' with 'Y'
        	printf("Modified s2: %s\n", s2);  // Print modified s2
    	}
    	else
    	{
        	printf("Character not found in s2\n");
    	}
	return 0;
}
*/
