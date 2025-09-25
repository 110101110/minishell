/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:17:26 by qizhang           #+#    #+#             */
/*   Updated: 2024/11/24 14:36:57 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, unsigned int len)
{
	char			*tmp_dst;
	const char		*tmp_src;
	unsigned int	i;

	if (!dst && !src)
		return (0);
	tmp_dst = (char *)dst;
	tmp_src = (const char *)src;
	i = 0;
	if (tmp_dst > tmp_src)
	{
		while (len-- > 0)
			tmp_dst[len] = tmp_src[len];
	}
	else
	{
		while (i < len)
		{
			tmp_dst[i] = tmp_src[i];
			i ++;
		}
	}
	return (dst);
}
