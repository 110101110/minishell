/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:31:14 by qizhang           #+#    #+#             */
/*   Updated: 2024/11/24 15:50:58 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

static int	to_trim(const char *set, char c);
static int	get_start(const char *s1, const char *set);
static int	get_end(const char *s1, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;
	char			*trim;

	if (!s1 || !set)
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set);
	if (end < start || start >= ft_strlen(s1))
		return (ft_strdup(""));
	trim = ft_calloc((end - start + 2), sizeof(char));
	if (!trim)
		return (NULL);
	i = 0;
	while (i < end + 1 - start)
	{
		trim[i] = s1[start + i];
		i ++;
	}
	trim[i] = 0;
	return (trim);
}

static int	get_start(const char *s1, const char *set)
{
	unsigned int	i;

	i = 0;
	while (to_trim(set, s1[i]) && s1[i])
	{
		i ++;
	}
	return (i);
}

static int	get_end(const char *s1, const char *set)
{
	unsigned int	i;

	if (ft_strlen(s1) == 0)
		return (0);
	i = ft_strlen(s1) - 1;
	while (to_trim(set, s1[i]) && i > 0)
	{
		i --;
	}
	return (i);
}

static int	to_trim(const char *set, char c)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
