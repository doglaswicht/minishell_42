/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:57:13 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 15:26:08 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>

void	init_signals(void)
{
	disable_echoctl();
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, signal_handler_parent);
	set_signal_code(0);
}

void	reset_signals(void)
{
	enable_echoctl();
	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
}
