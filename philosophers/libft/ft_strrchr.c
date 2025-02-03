/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:07:55 by nneves-a          #+#    #+#             */
/*   Updated: 2024/04/22 18:23:49 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ca;

	ca = (char) c;
	i = 0;
	while (s[i] != '\0')
		i++;
	if (ca == '\0')
	{
		return ((char *)&s[i]);
	}
	while (i >= 0)
	{
		if (s[i] == ca)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	s[] = "bonjour";
	int			c;
	char		*result;
	c = 's';
	result = ft_strrchr(s, c);
	printf("%s", result);
	return (0);
}
*/