/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:35:36 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/12 19:32:34 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	open_infile(t_data *data, t_command *cmd, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (set_error(data, file, 1, true));
	if (cmd->infile >= 0 && cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	cmd->infile = fd;
	return (true);
}

static bool	open_outfile(t_data *data, t_command *cmd, char *file, bool append)
{
	int	fd;

	if (append)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (set_error(data, file, 1, true));
	if (cmd->outfile >= 0 && cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (true);
}

bool	init_redirect(t_data *data, t_command *cmd, t_token **tok)
{
	if (!tok || !*tok || !(*tok)->next)
		return (false);
	if ((*tok)->type == INPUT)
	{
		*tok = (*tok)->next;
		return (open_infile(data, cmd, (*tok)->str));
	}
	if ((*tok)->type == TRUNC)
	{
		*tok = (*tok)->next;
		return (open_outfile(data, cmd, (*tok)->str, false));
	}
	if ((*tok)->type == APPEND)
	{
		*tok = (*tok)->next;
		return (open_outfile(data, cmd, (*tok)->str, true));
	}
	return (true);
}
