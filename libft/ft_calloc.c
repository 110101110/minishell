/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:32:05 by qizhang           #+#    #+#             */
/*   Updated: 2024/11/22 01:23:58 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(unsigned int count, unsigned int size)
{
	unsigned char	*tmp;
	unsigned int	i;

	i = 0;
	tmp = malloc(count * size);
	if (!tmp)
		return (0);
	while (i < count * size)
		tmp[i++] = 0;
	return (tmp);
}
