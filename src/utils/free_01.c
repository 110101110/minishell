/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:51:03 by chchen            #+#    #+#             */
/*   Updated: 2025/09/16 17:08:02 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*free_token(t_token *token)
{
	t_token	*curr;
	t_token	*tmp;

	if (!token)
		return (NULL);
	curr = token;
	while (curr)
	{
		tmp = curr->next;
		if (curr->prev)
			curr->prev->next = NULL;
		if (tmp)
			tmp->prev = NULL;
		free(curr->str);
		curr->str = NULL;
		free(curr);
		curr = tmp;
	}
	return (NULL);
}

void	free_all(t_data *data, char *error, int exit_code)
{
	if (data->cmd)
		free_cmd_list(&(data->cmd));
	if (data->env)
		free_envp(data->env);
	if (data->token)
		free_token(data->token);
	if (error)
		ft_putstr_fd(error, 2);
	clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	free(data);
	if (exit_code != -1)
		exit(exit_code);
}

char	**free_array(char **tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

bool	free_and_null(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (false);
}
