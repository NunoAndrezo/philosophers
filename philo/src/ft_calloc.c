/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:27:45 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/10 19:22:56 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	ft_bzero(void *s, size_t n)
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb == 0 || size == 0)
	{
		mem = malloc(0);
		if (mem == NULL)
			return (NULL);
		return (mem);
	}
	if ((nmemb * size) / nmemb != size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, size * nmemb);
	return (mem);
}
/*
		mem = malloc(0);
		if (!mem)
			return (NULL);
		return (mem);
		man calloc, If nmemb or size is 0,  then  calloc()  returns
    	either  NULL,  or a unique pointer value that can later 
		be successfully passed to free()

		if ((nmemb * size) / nmemb != size)
		return (NULL);
		If the multiplication of nmemb and size 
		would result in integer overflow, then 
		calloc() returns an error.
*/