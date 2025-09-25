/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_00.c                                             :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: chchen <chchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:08:47 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 15:51:37 by chchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_envp(t_envp *envp)
{
	t_envp	*tmp;

	if (!envp)
		return (0);
	while (envp)
	{
		tmp = envp->next;
		free(envp->str);
		free(envp);
		envp = tmp;
	}
	return (0);
}

static void	free_cmd(t_command *tmp)
{
	if (tmp->infile > 0)
		close(tmp->infile);
	tmp->infile = -2;
	if (tmp->outfile > 0)
		close(tmp->outfile);
	tmp->outfile = -2;
	free_array(tmp->param);
	tmp->param = NULL;
}

bool	free_cmd_list(t_command **cmd)
{
	t_command	*curr;
	t_command	*tmp;

	if (!cmd || !*cmd)
		return (false);
	curr = *cmd;
	while (curr)
	{
		tmp = curr->next;
		if (curr->prev)
			curr->prev->next = NULL;
		if (tmp)
			tmp->prev = NULL;
		free_cmd(curr);
		free(curr);
		curr = tmp;
	}
	*cmd = NULL;
	return (false);
}
