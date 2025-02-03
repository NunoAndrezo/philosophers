/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:56:25 by nneves-a          #+#    #+#             */
/*   Updated: 2024/09/12 18:49:11 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while ((str2[i] != '\0' || str1[i] != '\0') && (i < n))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	const char s1[] = "Moto\200";
	const char s2[] = "Moto\6";
	size_t x = 6;

	printf("%s\n", s1);
	printf("%s\n", s2);
	printf("%d\n", ft_strncmp(s1, s2, x));
	return (0);
}
*/
