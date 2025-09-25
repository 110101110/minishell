/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 00:37:00 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/18 00:41:41 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redirect(t_token *token)
{
	if (token->type == INPUT || token->type == TRUNC || token->type == APPEND)
		return (true);
	else
		return (false);
}

static bool	process_command(t_data *data, t_command *cmd, t_token **tok)
{
	cmd->param = token_arg(*tok);
	if (!cmd->param)
		return (set_error(data, "malloc error", 1, false));
	if (cmd->prev)
		cmd->infile = -2;
	if (cmd->next)
		cmd->outfile = -2;
	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type == HEREDOC)
		{
			if (!handle_heredoc(data, cmd, tok))
				return (false);
			continue ;
		}
		else if (is_redirect(*tok))
		{
			if (!init_redirect(data, cmd, tok))
				return (false);
		}
		*tok = (*tok)->next;
	}
	if (*tok && (*tok)->type == PIPE)
		*tok = (*tok)->next;
	return (true);
}

bool	init_cmd(t_data *data)
{
	t_token		*tok;
	t_command	*cmd;

	if (!create_cmd(data))
		return (set_error(data, "malloc error", 1, false));
	tok = data->token;
	cmd = data->cmd;
	while (cmd && tok)
	{
		if (!process_command(data, cmd, &tok))
			return (false);
		cmd = cmd->next;
	}
	return (true);
}
