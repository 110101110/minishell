/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:49:22 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/14 00:56:28 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_lst(t_envp **envp, char *str)
{
	t_envp	*curr;
	t_envp	*prev;
	int		len;

	if (!envp || !*envp || !str)
		return ;
	len = ft_strlen(str);
	curr = *envp;
	prev = *envp;
	while (curr)
	{
		if (!ft_strncmp(curr->str, str, len) && (curr->str[len] == '='
				|| curr->str[len] == '\0'))
		{
			if (prev)
				prev->next = curr->next;
			else
				*envp = curr->next;
			free(curr->str);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_envp **envp, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valide_id(args[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else if (exist_env(*envp, args[i]))
			remove_lst(envp, args[i]);
		i++;
	}
	return (status);
}
