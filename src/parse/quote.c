/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:06:23 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/12 14:17:42 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	update_quote(char c, char quote)
{
	if (is_quote(c))
	{
		if (quote == 0)
			quote = c;
		else if (quote == c)
			quote = 0;
	}
	return (quote);
}

int	check_quotes_error(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
		quote = update_quote(str[i++], quote);
	return (quote == 0);
}

void	assign_quote(t_token *token)
{
	if (token->dq > 0 && token->sq == 0)
		token->quote = DQ;
	else if (token->dq == 0 && token->sq > 0)
		token->quote = SQ;
	else if (token->dq == 0 && token->sq == 0)
		token->quote = 0;
	else
		token->quote = 1;
}

void	get_quote_type(t_token *token, const char *str)
{
	int	quote;
	int	prev_quote;

	token->dq = 0;
	token->sq = 0;
	quote = 0;
	while (*str)
	{
		prev_quote = quote;
		quote = update_quote(*str, quote);
		if (is_quote(*str) && prev_quote == 0)
		{
			if (*str == SQ)
				token->sq++;
			else if (*str == DQ)
				token->dq++;
		}
		str++;
	}
	assign_quote(token);
}

void	token_quote(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		get_quote_type(token, token->str);
		token = token->next;
	}
}
