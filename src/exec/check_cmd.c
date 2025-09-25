/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchen <chchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:29:58 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 15:13:55 by chchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_cmd_access(char **path, char *cmd, t_data *data)
{
	struct stat	info;

	if (stat(*path, &info) == -1)
	{
		free_and_null(path);
		return (set_error(data, cmd, 127, true));
	}
	if (S_ISDIR(info.st_mode))
	{
		free_and_null(path);
		return (set_error(data, cmd, 126, true));
	}
	if (access(*path, X_OK) == -1)
	{
		free_and_null(path);
		if (errno == EACCES)
			return (set_error(data, cmd, 126, true));
		else
			return (set_error(data, cmd, 127, true));
	}
	return (true);
}

bool	cmd_exist(char **path, t_data *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
	{
		*path = get_path(cmd, data->env, data);
		if (!*path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			data->exit_code = 127;
			return (false);
		}
	}
	else
	{
		*path = ft_strdup(cmd);
		if (!*path)
			return (set_error(data, "malloc error", 1, false));
	}
	return (check_cmd_access(path, cmd, data));
}
