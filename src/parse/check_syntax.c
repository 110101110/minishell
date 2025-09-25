/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchen <chchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:15:27 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 16:13:08 by chchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	syntax_error_msg(t_data *data, char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
	data->exit_code = 258;
	return (false);
}

bool	check_syntax(t_data *data, t_token *token)
{
	t_token	*curr;

	if (!token)
		return (true);
	if (token->type != CMD && token->type != ARG)
		return (syntax_error_msg(data, token->str));
	curr = token->next;
	while (curr && curr->next)
	{
		if (curr->type == -1)
			return (syntax_error_msg(data, curr->str));
		else if ((curr->type > 0 && curr->type < 6) && (curr->next->type > 0
				&& curr->next->type < 6))
			return (syntax_error_msg(data, curr->next->str));
		curr = curr->next;
	}
	if (curr && curr->type != CMD && curr->type != ARG)
		return (syntax_error_msg(data, curr->str));
	return (true);
}
