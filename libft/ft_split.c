/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:21:42 by qizhang           #+#    #+#             */
/*   Updated: 2024/11/24 20:18:08 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

static void	*ft_free(char **str, unsigned int words_allocated)
{
	unsigned int	i;

	i = 0;
	while (i < words_allocated)
	{
		if (str[i])
			free(str[i]);
		i ++;
	}
	free(str);
	return (NULL);
}

static unsigned int	count_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	word;

	i = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && word == 0)
		{
			word = 1;
			i++;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (i);
}

char	**word_allocate(const char *s, char **str, char c)
{
	unsigned int	i;
	unsigned int	j;
	int				start;

	start = -1 ;
	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start == -1)
			start = i;
		else if ((s[i] == c || s[i] == 0) && start != -1)
		{
			str[j] = ft_substr(s, start, (i - start));
			if (!(str[j]))
			{
				return (ft_free(str, j));
			}
			start = -1;
			j ++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	unsigned int	word_count;
	char			**str;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	str = (char **) malloc((word_count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str = word_allocate(s, str, c);
	return (str);
}
