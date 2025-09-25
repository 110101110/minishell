/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:27:25 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/19 17:36:05 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	init_data(t_data *data, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	data->cmd = NULL;
	data->env = NULL;
	data->token = NULL;
	data->exit_code = 0;
	if (!get_env(data, env))
		free_all(data, "error: malloc failed", 1);
}

bool	empty_line(char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	len = ft_strlen(line);
	if (i == len)
		return (true);
	else
		return (false);
}

bool	parse_line(t_data *data, char *line)
{
	if (empty_line(line))
	{
		free(line);
		return (false);
	}
	add_history(line);
	if (!check_quotes_error(line))
		return (free(line), set_error(data, "unclosed quote", 1, false));
	data->token = tokenize_line(line);
	if (!data->token)
	{
		free(line);
		return (set_error(data, "malloc error", 1, false));
	}
	free(line);
	assign_token(data->token);
	token_quote(data->token);
	if (!check_syntax(data, data->token))
		return (false);
	if (!expand_and_remove(data))
	{
		free_token(data->token);
		return (set_error(data, "malloc error", 1, false));
	}
	return (true);
}

static void	process_cmd(t_data *data, char *line)
{
	if (!parse_line(data, line))
		return ;
	if (!init_cmd(data))
	{
		data->token = free_token(data->token);
		return ;
	}
	if (!exec_cmd(data, data->cmd))
	{
		free_cmd_list(&data->cmd);
		data->cmd = NULL;
		data->token = free_token(data->token);
		return ;
	}
	free_cmd_list(&data->cmd);
	data->cmd = NULL;
	data->token = free_token(data->token);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data, ac, av, env);
	rl_catch_signals = 0;
	while (1)
	{
		set_signals_prompt();
		line = readline("minishell> ");
		if (!line)
			free_all(data, "exit\n", data->exit_code);
		if (g_signal_received)
		{
			data->exit_code = 130;
			g_signal_received = 0;
		}
		process_cmd(data, line);
	}
	return (0);
}
