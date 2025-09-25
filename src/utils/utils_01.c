/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchen <chchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:48:02 by chchen            #+#    #+#             */
/*   Updated: 2025/09/16 15:49:51 by chchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_array(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

bool	is_var(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*copy_str(char *src, int start, int end)
{
	int		i;
	int		j;
	int		len;
	char	*dst;

	if (!src || start < 0 || end < start)
		return (NULL);
	i = start;
	j = 0;
	len = end - start;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (i < end && src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst);
}

int	get_env(t_data *data, char **env)
{
	t_envp	*head;
	t_envp	*tail;
	t_envp	*node;
	int		i;

	i = 0;
	head = NULL;
	tail = NULL;
	while (env[i])
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		if (!node)
			return (free_envp(head));
		node->str = ft_strdup(env[i]);
		node->next = NULL;
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	data->env = head;
	return (1);
}

bool	set_error(t_data *data, const char *msg, int code, bool perror_flag)
{
	if (msg)
	{
		ft_putstr_fd("minishell: ", 2);
		if (perror_flag)
			perror(msg);
		else
		{
			ft_putstr_fd((char *)msg, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	data->exit_code = code;
	return (false);
}
