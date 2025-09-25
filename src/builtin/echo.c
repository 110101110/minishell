/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:47:53 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/13 23:17:23 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	new_line(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (true);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (true);
	return (false);
}

int	ft_echo(char **args)
{
	bool	new_l;
	int		i;

	new_l = true;
	i = 1;
	if (args[i] && new_line(args[i]) == false)
	{
		new_l = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_l == true)
		printf("\n");
	return (0);
}
