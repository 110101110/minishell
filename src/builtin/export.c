/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:49:18 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/17 23:44:01 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_var(char *str)
{
	char	*eq;
	int		len;

	write(1, "declare -x ", 11);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		len = eq - str + 1;
		write(1, str, len);
		write(1, "\"", 1);
		write(1, eq + 1, ft_strlen(eq + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
}

int	export_no_args(t_data *data, t_envp *envp)
{
	char	**env;
	int		i;

	env = lst_array(envp);
	if (!env)
		return (set_error(data, "malloc", 1, true), 1);
	sort_array(env);
	i = 0;
	while (env[i])
	{
		write_var(env[i]);
		i++;
	}
	free_array(env);
	return (0);
}

int	add_to_lst(t_data *data, t_envp **envp, char *str)
{
	t_envp	*last;
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (set_error(data, "malloc", 1, true), 1);
	node->str = ft_strdup(str);
	if (!node->str)
	{
		free(node);
		return (set_error(data, "malloc", 1, true), 1);
	}
	node->next = NULL;
	if (!*envp)
		*envp = node;
	else
	{
		last = *envp;
		while (last->next)
			last = last->next;
		last->next = node;
	}
	return (0);
}

int	ft_export(t_data *data, t_envp **envp, char **args)
{
	int	status;
	int	i;

	count_array(args);
	if (count_array(args) == 1 && *envp)
		return (export_no_args(data, *envp));
	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valide_id(args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else if (exist_env(*envp, args[i]))
			status = replace_env(data, *envp, args[i]);
		else
			status = add_to_lst(data, envp, args[i]);
		i++;
	}
	return (status);
}
