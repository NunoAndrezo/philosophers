/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:43:12 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/09 23:00:55 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (s1[len - 1] && ft_strchr(set, s1[len - 1]) && len > i)
		len--;
	str = (char *)malloc(sizeof(char) * (len - i + 1));
	if (str == NULL)
		return (NULL);
	while (i + 1 <= len)
	{
		str[j++] = s1[i++];
	}
	str[j] = '\0';
	return (str);
}
/*
int	main(void)
{
	char const	s1[] = "aabbabababoto Ratabaabbbbaabba";
	char const	s2[] = "ab";
	char 		*s3;

	s3 = ft_strtrim(s1, s2);
	printf("%s\n", s3);
	free(s3);
	return (0);
}
*/
