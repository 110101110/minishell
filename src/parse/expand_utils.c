/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:31:56 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/18 21:28:51 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(t_envp *envp, char *var)
{
	t_envp	*head;
	int		i;
	int		len_var;
	int		len;

	if (!var)
		return (ft_strdup(""));
	head = envp;
	len_var = ft_strlen(var);
	while (head != NULL)
	{
		i = 0;
		len = ft_strlen(head->str);
		while (head->str[i] && head->str[i] != '=')
			i++;
		if (i == len_var && ft_strncmp(var, head->str, i) == 0)
			return (copy_str(head->str, len_var + 1, len));
		head = head->next;
	}
	return (ft_strdup(""));
}

bool	append_str(char **dst, int *j, char *val)
{
	char	*new_buf;
	int		len;
	int		k;

	if (!val)
		return (true);
	len = ft_strlen(val);
	new_buf = malloc(*j + len + 1);
	if (!new_buf)
		return (false);
	if (dst)
		ft_memcpy(new_buf, *dst, *j);
	k = 0;
	while (val[k])
		new_buf[(*j)++] = val[k++];
	new_buf[*j] = '\0';
	free(*dst);
	*dst = new_buf;
	return (true);
}

bool	append_char(char **dst, int *j, char c)
{
	char	*new_buf;

	new_buf = malloc(*j + 2);
	if (!new_buf)
		return (false);
	if (dst)
		ft_memcpy(new_buf, *dst, *j);
	new_buf[(*j)] = c;
	new_buf[(*j) + 1] = '\0';
	free(*dst);
	*dst = new_buf;
	(*j)++;
	return (true);
}

bool	get_value(char *src, t_expand_ctx *exp, t_data *data)
{
	int		start;
	char	*var;
	char	*val;

	var = NULL;
	val = NULL;
	start = exp->i;
	if (src[(exp->i)++] == '?')
		val = ft_itoa(data->exit_code);
	else
	{
		while (is_var(src[exp->i]))
			(exp->i)++;
		var = copy_str(src, start, (exp->i));
		if (!var)
			return (false);
		val = ft_getenv(data->env, var);
		free(var);
	}
	if (!val)
		return (false);
	if (!append_str(&exp->buf, &exp->j, val))
		return (free_and_null(&exp->buf) && free_and_null(&val));
	free(val);
	return (true);
}
