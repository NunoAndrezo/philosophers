/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:57:00 by nneves-a          #+#    #+#             */
/*   Updated: 2024/05/09 23:00:48 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "libft.h"
#include <string.h>

static size_t	ft_count_words(char const *s, char c);
static int		ft_fill(char **argv, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**word_argv;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	word_argv = (char **)malloc(sizeof(char *) * (words + 1));
	if (word_argv == NULL)
		return (NULL);
	word_argv[words] = NULL;
	if (ft_fill(word_argv, s, c))
		return (NULL);
	return (word_argv);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words;
	bool	in_word;

	words = 0;
	while (*s != '\0')
	{
		in_word = false;
		while (*s != '\0' && *s == c)
			s++;
		while (*s != '\0' && *s != c)
		{
			if (in_word == false)
			{
				words++;
				in_word = true;
			}
			s++;
		}
	}
	return (words);
}

static int	ft_free(char **word_argv)
{
	int	i;

	i = 0;
	while (word_argv[i])
	{
		free(word_argv[i]);
		i++;
	}
	free(word_argv);
	return (1);
}

static int	ft_fill(char **word_argv, char const *s, char c)
{
	size_t	len;
	int		a;

	a = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			word_argv[a] = malloc(len + 1);
			if (word_argv[a] == NULL)
				return (ft_free(word_argv));
			ft_memcpy(word_argv[a], s - len, len);
			word_argv[a++][len] = '\0';
		}
	}
	word_argv[a] = NULL;
	return (0);
}
//return 0 if all mallocs went fine, otherwise 1
/*
int main(void)
{
    char const *input_string = "Hello,world,,this,is,,a,test";
    char **result;

    printf("Input string: %s\n", input_string);

    result = ft_split(input_string, ',');
    if (result == NULL)
    {
        printf("Split failed: NULL returned.\n");
        free(result);
		return 1;
    }

    printf("Split result:\n");
    for (int i = 0; result[i] != NULL; i++)
    {
        printf("[%d]: \"%s\"\n", i, result[i]);
		free(result[i]);
    }
	free(result);
	return 0;
}
*/
/*
steps:
1st - count the words! Or tokens in str (if the delimeter is not spaces)
2nd - Allocate memory for the array of strings
3rd - Cpy the token in the correct position
*/
