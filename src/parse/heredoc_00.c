/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:20:43 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/19 18:35:27 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_line(t_data *data, char *line)
{
	t_token	tmp;
	char	*res;

	if (!line)
		return (NULL);
	tmp.str = ft_strdup(line);
	if (!tmp.str)
		return (NULL);
	tmp.quote = 0;
	tmp.next = NULL;
	tmp.prev = NULL;
	if (!expansion(data, &tmp))
	{
		free(tmp.str);
		return (NULL);
	}
	res = tmp.str;
	return (res);
}

bool	write_heredoc(t_data *data, int fd, char *line, bool expand)
{
	char	*buf;

	if (!line)
		return (set_error(data, "write_heredoc: line is NULL\n", 1, false));
	if (expand && line[0] != '\0')
	{
		buf = expand_line(data, line);
		if (!buf)
			return (set_error(data, "malloc failed\n", 1, false));
		ft_putstr_fd(buf, fd);
		write(fd, "\n", 1);
		free(buf);
	}
	else
	{
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
	}
	return (true);
}

void	print_eof_warning(char *delim)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted '", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}
