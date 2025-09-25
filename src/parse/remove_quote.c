/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:11:27 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/08 18:11:27 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	remove_quote(t_token *token)
{
	char	*buf;
	int		i;
	int		j;
	char	quote;

	buf = malloc(ft_strlen(token->str) + 1);
	if (!buf)
		return (false);
	i = 0;
	j = 0;
	quote = 0;
	while (token->str[i])
	{
		if (is_quote(token->str[i]) && (quote == 0 || quote == token->str[i]))
		{
			quote = update_quote(token->str[i], quote);
			i++;
		}
		else
			buf[j++] = token->str[i++];
	}
	buf[j] = '\0';
	free(token->str);
	token->str = buf;
	return (true);
}

bool	expand_and_remove(t_data *data)
{
	t_token	*curr;

	curr = data->token;
	while (curr)
	{
		if (curr->quote == 0)
		{
			if (!expansion(data, curr))
				return (false);
		}
		else
		{
			if (!expansion(data, curr) || !remove_quote(curr))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}
