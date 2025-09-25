/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:27:17 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 17:01:07 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_envp(t_envp *envp)
{
	while (envp)
	{
		if (ft_strncmp(envp->str, "PATH=", 5) == 0)
			return (envp->str + 5);
		envp = envp->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_envp *envp, t_data *data)
{
	char	*env_path;
	char	**allpaths;
	char	*exec;
	char	*path;
	int		i;

	env_path = find_envp(envp);
	if (!env_path)
		return (NULL);
	allpaths = ft_split(env_path, ':');
	if (!allpaths)
		return (set_error(data, "malloc error", 1, false), NULL);
	i = -1;
	while (allpaths[++i])
	{
		path = ft_strjoin(allpaths[i], "/");
		exec = ft_strjoin(path, cmd);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
			return (free_array(allpaths), exec);
		free(exec);
	}
	free_array(allpaths);
	return (NULL);
}
