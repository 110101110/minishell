/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:43:53 by qizhang           #+#    #+#             */
/*   Updated: 2025/08/01 21:43:53 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_meta(char *str)
{
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '"'))
	{
		if (ft_strchr(str, '|') || ft_strchr(str, '>')
			|| ft_strchr(str, '<'))
			return (true);
	}
	return (false);
}

int	special_type(char *str)
{
	if (is_meta(str))
	{
		if (!ft_strncmp (str, "|", 2))
			return (PIPE);
		else if (!ft_strncmp(str, "<", 2))
			return (INPUT);
		else if (!ft_strncmp(str, "<<", 3))
			return (HEREDOC);
		else if (!ft_strncmp(str, ">", 2))
			return (TRUNC);
		else if (!ft_strncmp(str, ">>", 3))
			return (APPEND);
		else
			return (-1);
	}
	else
		return (0);
}

void	assign_token(t_token *token)
{
	t_token	*curr;

	if (!token)
		return ;
	token->type = special_type(token->str);
	if (token->type == 0)
		token->type = CMD;
	curr = token->next;
	while (curr)
	{
		curr->type = special_type(curr->str);
		if (curr->type == 0)
		{
			if (curr->prev && curr->prev->type == PIPE)
				curr->type = CMD;
			else
				curr->type = ARG;
		}
		curr = curr->next;
	}
}
