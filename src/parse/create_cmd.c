/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:02:58 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/19 17:22:38 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(t_token *token)
{
	int	count;

	if (!token)
		return (0);
	count = 1;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

void	init_node(t_command *node)
{
	node->param = NULL;
	node->infile = -1;
	node->outfile = -1;
	node->pid = -1;
	node->next = NULL;
	node->prev = NULL;
}

bool	create_cmd(t_data *data)
{
	t_command	*node;
	t_command	*head;
	t_command	*last;
	int			cmd_nbr;

	cmd_nbr = count_cmd(data->token);
	head = NULL;
	last = NULL;
	while (cmd_nbr-- > 0)
	{
		node = malloc(sizeof(t_command));
		if (!node)
			return (free_cmd_list(&head));
		init_node(node);
		if (head == NULL)
			head = node;
		else
		{
			last->next = node;
			node->prev = last;
		}
		last = node;
	}
	data->cmd = head;
	return (true);
}

int	count_arg(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if ((token->type == CMD) || (token->type == ARG && token->prev
				&& !is_redirect(token->prev)))
		{
			if (!token->prev || token->prev->type != HEREDOC)
				count++;
		}
		token = token->next;
	}
	return (count);
}

char	**token_arg(t_token *token)
{
	char	**arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(char *) * (count_arg(token) + 1));
	if (!arg)
		return (NULL);
	while (token && token->type != PIPE)
	{
		if ((token->type == CMD) || (token->type == ARG && token->prev
				&& !is_redirect(token->prev)))
		{
			if (!token->prev || token->prev->type != HEREDOC)
			{
				arg[i] = ft_strdup(token->str);
				if (!arg[i])
					return (free_array(arg));
				i++;
			}
		}
		token = token->next;
	}
	arg[i] = NULL;
	return (arg);
}
