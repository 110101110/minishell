/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_01.c                                          :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: chchen <chchen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:02:29 by qizhang           #+#    #+#             */
/*   Updated: 2025/09/16 20:43:03 by chchen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_handlers(int sig, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(sig, &sa, NULL);
}

void	set_signals_prompt(void)
{
	g_signal_received = 0;
	set_handlers(SIGINT, sigint_prompt);
	set_handlers(SIGQUIT, sigquit_ignore);
}

void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signals_parent_wait(void)
{
	set_handlers(SIGINT, SIG_IGN);
	set_handlers(SIGQUIT, SIG_IGN);
}

void	set_signal_heredoc(void)
{
	g_signal_received = 0;
	set_handlers(SIGINT, sigint_heredoc);
	set_handlers(SIGQUIT, sigquit_ignore);
}
