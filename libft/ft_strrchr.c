/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:21:08 by qizhang           #+#    #+#             */
/*   Updated: 2024/11/22 12:59:55 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;
	char		cc;

	cc = (char)c;
	last = 0;
	while (*s)
	{
		if (*s == cc)
			last = s;
		s++;
	}
	if (cc == 0)
		return ((char *)s);
	return ((char *)last);
}
