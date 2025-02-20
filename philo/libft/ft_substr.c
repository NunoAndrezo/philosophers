/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:37:43 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/07 16:41:13 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	else if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
			substr[j++] = s[i];
		i++;
	}
	substr[j] = '\0';
	return (substr);
}
/*
int main(void)
{
    const char *s = "Hello, World!";
    unsigned int start = 7;
    size_t len = 9;

    char *substr = ft_substr(s, start, len);
    if (substr != NULL)
    {
        printf("Substring: %s\n", substr);
        // Free the allocated memory when done using the substring
        free(substr);
    }
    else
    {
        printf("Failed to allocate memory for substring.\n");
    }
    return (0);
}
*/
/* int	main(void)
{
	char const s[] = "";

	printf("%s", ft_substr(s, 0, 1));
	return (0);
} */
