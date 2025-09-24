/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:14:00 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 15:30:11 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	init_signals(void);
void	reset_signals(void);

void	signal_handler_parent(int sig);
void	signal_handler_child(int sig);

void	disable_echoctl(void);
void	enable_echoctl(void);

#endif
