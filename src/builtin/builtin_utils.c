/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:20:56 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 01:07:03 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_array(char **arr)
{
	int	i;
	int	n;
	int	swapped;

	if (!arr)
		return ;
	n = 0;
	while (arr[n])
		n++;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < n - 1)
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				ft_swap(&arr[i], &arr[i + 1]);
				swapped = 1;
			}
			i++;
		}
		n--;
	}
}

bool	is_valide_id(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	exist_env(t_envp *env, char *str)
{
	t_envp	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] == '='
				|| tmp->str[i] == '\0'))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	replace_env(t_data *data, t_envp *env, char *str)
{
	t_envp	*tmp;
	int		i;

	if (!env || !str)
		return (1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, str, i) == 0 && (tmp->str[i] == '='
				|| tmp->str[i] == '\0'))
		{
			free(tmp->str);
			tmp->str = ft_strdup(str);
			if (!tmp->str)
				return (set_error(data, "malloc", 1, true), 1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
