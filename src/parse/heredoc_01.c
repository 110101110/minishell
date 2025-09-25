/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:20:43 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/19 19:04:28 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_heredoc_line(t_data *data, int fd, t_token *delim, char *line)
{
	bool	expand;

	expand = (delim->quote != SQ);
	if (g_signal_received)
		return (free(line), false);
	if (!ft_strncmp(line, delim->str, INT_MAX))
		return (free(line), true);
	if (!write_heredoc(data, fd, line, expand))
		return (free(line), false);
	free(line);
	return (false);
}

static bool	read_heredoc(t_data *data, int fd, t_token *delim)
{
	char	*line;
	bool	done;

	set_signal_heredoc();
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		done = handle_heredoc_line(data, fd, delim, line);
		if (g_signal_received || done)
			break ;
	}
	if (!line && !g_signal_received)
		print_eof_warning(delim->str);
	if (g_signal_received)
	{
		free_cmd_list(&data->cmd);
		return (data->exit_code = 130, g_signal_received = 0, false);
	}
	return (true);
}

static bool	setup_heredoc(t_data *data, int *fd, int *saved_in, t_token **tok)
{
	*tok = (*tok)->next;
	if (!*tok)
		return (false);
	*fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd < 0)
		return (set_error(data, "heredoc", 1, true));
	*saved_in = dup(STDIN_FILENO);
	if (*saved_in < 0)
	{
		close(*fd);
		return (set_error(data, "dup failed", 1, true));
	}
	if (!read_heredoc(data, *fd, *tok))
	{
		close(*fd);
		unlink(".heredoc.tmp");
		dup2(*saved_in, STDIN_FILENO);
		close(*saved_in);
		return (false);
	}
	close(*fd);
	return (true);
}

bool	handle_heredoc(t_data *data, t_command *cmd, t_token **tok)
{
	int	fd;
	int	saved_in;

	if (!setup_heredoc(data, &fd, &saved_in, tok))
		return (false);
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd < 0)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
		return (set_error(data, "heredoc", 1, true));
	}
	cmd->infile = fd;
	dup2(saved_in, STDIN_FILENO);
	close(saved_in);
	unlink(".heredoc.tmp");
	*tok = (*tok)->next;
	return (true);
}
