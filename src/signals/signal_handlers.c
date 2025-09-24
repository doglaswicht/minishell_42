/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:57:11 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:28:25 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

void	signal_handler_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(1, "\n", 1);
		if (rl_readline_state & RL_STATE_READCMD)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		if (rl_readline_state & RL_STATE_READCMD)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		write(1, "Quit (core dumped)\n", 19);
	}
}
