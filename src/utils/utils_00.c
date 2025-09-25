/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchen <chchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:12:14 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 15:49:46 by chchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

int	len_cmd(t_command *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	len_envp(t_envp *envp)
{
	t_envp	*tmp;
	int		i;

	if (!envp)
		return (0);
	i = 0;
	tmp = envp;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**lst_array(t_envp *envp)
{
	int		i;
	t_envp	*tmp;
	char	**arr;

	tmp = envp;
	i = len_envp(tmp);
	arr = malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		arr[i] = ft_strdup(tmp->str);
		if (!arr[i])
			return (free_array(arr));
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}
