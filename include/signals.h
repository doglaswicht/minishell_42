/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:14:00 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/05 16:51:58 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	init_signals(void);
void	reset_signals(void);
void	signal_handler_parent(int sig);
void	signal_handler_child(int sig);
void	enable_echoctl(void);
void	disable_echoctl(void);
void	set_signal_code(int code);
int		get_signal_code(void);

#endif
