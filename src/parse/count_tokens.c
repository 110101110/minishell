/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:27:41 by qizhang           #+#    #+#             */
/*   Updated: 2025/08/15 17:15:36 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	skip_quote(char *line, int *i)
{
	char	quote;

	if (!is_quote(line[*i]))
		return (0);
	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (quote == line[*i])
		quote = 0;
	return (quote);
}

static void	start_token(int *count, int *in_token)
{
	if (!*in_token)
	{
		(*count)++;
		(*in_token) = 1;
	}
}

int	count_tokens(char *line)
{
	int		count;
	int		i;
	int		in_token;
	char	quote;

	count = 0;
	i = 0;
	quote = 0;
	in_token = 0;
	while (line[i])
	{
		if (!quote && is_space(line[i]))
		{
			in_token = 0;
			i++;
			continue ;
		}
		start_token(&count, &in_token);
		if (!quote)
			quote = skip_quote(line, &i);
		if (!quote)
			i++;
	}
	return (count);
}
