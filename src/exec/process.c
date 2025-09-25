/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:30:33 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/18 01:55:20 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_pipes(int *p_fd)
{
	if (!p_fd)
		return ;
	if (p_fd[0] >= 0)
	{
		close(p_fd[0]);
		p_fd[0] = -1;
	}
	if (p_fd[1] >= 0)
	{
		close(p_fd[1]);
		p_fd[1] = -1;
	}
}

void	redirect(t_command *cmd, int *p_fd, int prev_fd)
{
	if (prev_fd >= 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->infile >= 0 && cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0 && cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	if (cmd->next && p_fd && p_fd[1] >= 0)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		close_pipes(p_fd);
	}
}

static void	set_fd(t_command *cmd, int *p_fd, int prev_fd)
{
	if (prev_fd >= 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->infile >= 0 && cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->next && p_fd && p_fd[1] >= 0)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		close_pipes(p_fd);
	}
}

void	child_process(t_data *data, t_command *cmd, int *p_fd, int prev_fd)
{
	char	*path;
	char	**env;

	set_fd(cmd, p_fd, prev_fd);
	if (is_builtin(cmd->param[0]))
		builtin(data, cmd, NULL, -1);
	path = NULL;
	if (!cmd_exist(&path, data, cmd->param[0]))
		exit(data->exit_code);
	env = lst_array(data->env);
	if (!env)
	{
		ft_putstr_fd("minishell: malloc error\n", 2);
		free(path);
		exit(1);
	}
	set_signals_child();
	execve(path, cmd->param, env);
	free_array(env);
	free(path);
	perror("execve");
	exit(126);
}

void	parent_process(t_command *cmd, int *p_fd, int prev_fd)
{
	if (prev_fd >= 0)
		close(prev_fd);
	if (cmd->outfile >= 0 && cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	if (cmd->infile >= 0 && cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->next && p_fd)
	{
		cmd->next->infile = p_fd[0];
		close(p_fd[1]);
	}
	else
		close_pipes(p_fd);
}

/*p_fd[0] is read end, means output of the pipe*/
/*p_fd[1] is write end, means input of the pipe*/
