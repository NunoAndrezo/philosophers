/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:27:45 by nneves-a          #+#    #+#             */
/*   Updated: 2024/12/15 03:24:48 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

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