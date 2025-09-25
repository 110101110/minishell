/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchen <chchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:49:10 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 15:59:09 by chchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_data *data, char **args)
{
	long	exit;

	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_all(data, NULL, 255);
		}
		else if (args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			data->exit_code = 1;
			return ;
		}
		exit = ft_atol(args[1]) % 256;
		if (exit < 0)
			exit += 256;
		free_all(data, NULL, (int)exit);
	}
	else
		free_all(data, NULL, data->exit_code);
}
