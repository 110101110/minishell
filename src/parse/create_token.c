/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:03:47 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/12 13:35:15 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	token_len(char *line, int *index)
{
	int		j;
	char	quote;
	int		len;

	j = *index;
	quote = 0;
	len = 0;
	while (line[j] && (!is_space(line[j]) || quote))
	{
		if (!quote && is_quote(line[j]))
			quote = line[j++];
		else if (quote && line[j] == quote)
		{
			quote = 0;
			j++;
		}
		else
			j++;
		len++;
	}
	return (len);
}

static char	*extract_token(char *line, int *index)
{
	int		i;
	int		j;
	int		len;
	char	*token;

	while (line[*index] && is_space(line[*index]))
		(*index)++;
	i = *index;
	token = NULL;
	len = token_len(line, index);
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	j = 0;
	while (j < len)
		token[j++] = line[i++];
	token[j] = '\0';
	*index = i;
	return (token);
}

t_token	*create_node(char *line, int *index)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = extract_token(line, index);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*tokenize_line(char *line)
{
	t_token	*node;
	t_token	*head;
	t_token	*last;
	int		count;
	int		index;

	count = count_tokens(line);
	index = 0;
	head = create_node(line, &index);
	if (!head)
		return (NULL);
	last = head;
	while (count > 1)
	{
		node = create_node(line, &index);
		if (!node)
			return (free_token(head));
		last->next = node;
		node->prev = last;
		last = node;
		count--;
	}
	return (head);
}
