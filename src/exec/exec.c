/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:07:01 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/18 22:08:24 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	wait_all(t_data *data)
{
	int		status;
	pid_t	pid;

	set_signals_parent_wait();
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == data->last_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				data->exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
				else if (WTERMSIG(status) == SIGQUIT)
					write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			}
		}
		pid = waitpid(-1, &status, 0);
	}
	set_signals_prompt();
}

static bool	handle_pipe(t_data *data, t_command *cmd, int *p_fd)
{
	if (!cmd->next)
	{
		p_fd[0] = -1;
		p_fd[1] = -1;
		return (true);
	}
	if (pipe(p_fd) < 0)
		return (set_error(data, "pipe", 1, true));
	return (true);
}

static bool	exec_one(t_data *data, t_command *cmd, int prev_fd)
{
	int		p_fd[2];
	pid_t	pid;

	if (!handle_pipe(data, cmd, p_fd))
		return (false);
	pid = fork();
	if (pid < 0)
		return (set_error(data, "fork", 1, true));
	if (pid == 0)
		child_process(data, cmd, p_fd, prev_fd);
	parent_process(cmd, p_fd, prev_fd);
	if (!cmd->next)
		data->last_pid = pid;
	return (true);
}

static bool	exec_sdl_bltn(t_data *data, t_command *cmd)
{
	int		saved_in;
	int		saved_out;
	int		p_fd[2];
	bool	ok;

	p_fd[0] = -1;
	p_fd[1] = -1;
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_in < 0 || saved_out < 0)
		return (set_error(data, "dup", 1, true));
	set_signals_prompt();
	redirect(cmd, p_fd, -1);
	ok = launch_builtin(data, cmd);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	set_signals_prompt();
	return (ok);
}

bool	exec_cmd(t_data *data, t_command *cmd)
{
	int	prev_fd;

	prev_fd = -1;
	if (is_builtin(cmd->param[0]) && !cmd->next)
		return (exec_sdl_bltn(data, cmd));
	while (cmd)
	{
		if (!exec_one(data, cmd, prev_fd))
			return (false);
		if (cmd->next)
			prev_fd = cmd->next->infile;
		else
			prev_fd = -1;
		cmd = cmd->next;
	}
	wait_all(data);
	return (true);
}

/*p_fd[0] is read end, means output of the pipe*/
/*p_fd[1] is write end, means input of the pipe*/
