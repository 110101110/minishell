/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:37:19 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/17 20:44:16 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

bool	is_builtin(char *str)
{
	if (!str)
		return (false);
	if (ft_strncmp("echo", str, 5) == 0 || ft_strncmp("cd", str, 3) == 0
		|| ft_strncmp("pwd", str, 4) == 0 || ft_strncmp("export", str, 7) == 0
		|| ft_strncmp("unset", str, 6) == 0 || ft_strncmp("env", str, 4) == 0
		|| ft_strncmp("exit", str, 5) == 0)
		return (true);
	return (false);
}

bool	launch_builtin(t_data *data, t_command *cmd)
{
	if (!cmd || !cmd->param || !cmd->param[0])
		return (false);
	if (ft_strncmp(cmd->param[0], "echo", 5) == 0)
		data->exit_code = ft_echo(cmd->param);
	else if (ft_strncmp(cmd->param[0], "cd", 3) == 0)
		data->exit_code = ft_cd(data, &data->env, cmd->param);
	else if (ft_strncmp(cmd->param[0], "pwd", 4) == 0)
		data->exit_code = ft_pwd();
	else if (ft_strncmp(cmd->param[0], "export", 7) == 0)
		data->exit_code = ft_export(data, &data->env, cmd->param);
	else if (ft_strncmp(cmd->param[0], "unset", 6) == 0)
		data->exit_code = ft_unset(&data->env, cmd->param);
	else if (ft_strncmp(cmd->param[0], "env", 4) == 0)
		data->exit_code = ft_env(data->env);
	else if (ft_strncmp(cmd->param[0], "exit", 5) == 0)
		ft_exit(data, cmd->param);
	else
		return (false);
	return (true);
}

void	builtin(t_data *data, t_command *cmd, int *p_fd, int prev_fd)
{
	redirect(cmd, p_fd, prev_fd);
	launch_builtin(data, cmd);
	exit(data->exit_code);
}
