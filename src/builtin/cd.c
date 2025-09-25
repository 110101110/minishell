/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:46:41 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/15 16:30:31 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_oldpwd(t_data *data, t_envp **envp)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	*args[3];

	if (!getcwd(cwd, PATH_MAX))
		return (set_error(data, "getcwd", 1, true), 1);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (!old_pwd)
		return (set_error(data, "malloc", 1, true), 1);
	args[0] = "export";
	args[1] = old_pwd;
	args[2] = NULL;
	ft_export(data, envp, args);
	free(old_pwd);
	return (0);
}

static int	update_pwd(t_data *data, t_envp **envp)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	char	*args[3];

	if (!getcwd(cwd, PATH_MAX))
		return (set_error(data, "getcwd", 1, true), 1);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (set_error(data, "malloc", 1, true), 1);
	args[0] = "export";
	args[1] = pwd;
	args[2] = NULL;
	ft_export(data, envp, args);
	free(pwd);
	return (0);
}

int	ft_cd(t_data *data, t_envp **envp, char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("cd: missing argument\n", 2);
		return (1);
	}
	if (update_oldpwd(data, envp))
		return (1);
	if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(args[1]);
		return (1);
	}
	return (update_pwd(data, envp));
}
