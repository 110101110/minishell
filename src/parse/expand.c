/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:26:05 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/19 18:18:15 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	handle_dollar_quote(t_expand_ctx *exp, char *str)
{
	exp->i++;
	while (str[exp->i] && !is_quote(str[exp->i]))
	{
		if (!append_char(&exp->buf, &exp->j, str[exp->i++]))
			return (false);
	}
	if (is_quote(str[exp->i]))
		exp->i++;
	return (true);
}

static bool	expand_special(t_expand_ctx *exp, t_data *data, char *str,
		char *quote)
{
	if (is_quote(str[exp->i]) && (*quote == 0 || *quote == str[exp->i]))
	{
		*quote = update_quote(str[exp->i], *quote);
		if (!append_char(&exp->buf, &exp->j, str[(exp->i)++]))
			return (false);
		return (true);
	}
	if (str[exp->i] == '$' && *quote != '\'')
	{
		exp->i++;
		if (is_quote(str[exp->i]))
			return (handle_dollar_quote(exp, str));
		if (str[exp->i] == ' ' || str[exp->i] == '\0')
		{
			if (!append_char(&exp->buf, &exp->j, '$'))
				return (false);
		}
		else
			return (get_value(str, exp, data));
		return (true);
	}
	else if (!append_char(&exp->buf, &exp->j, str[(exp->i)++]))
		return (false);
	return (true);
}

bool	expansion(t_data *data, t_token *token)
{
	t_expand_ctx	exp;
	char			quote;

	exp.i = 0;
	exp.j = 0;
	exp.buf = NULL;
	quote = 0;
	while (token->str[exp.i])
	{
		if (!expand_special(&exp, data, token->str, &quote))
			return (free_and_null(&exp.buf));
	}
	free(token->str);
	token->str = exp.buf;
	return (true);
}
