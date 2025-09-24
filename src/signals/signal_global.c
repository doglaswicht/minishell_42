/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:57:09 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/27 15:59:13 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	set_signal_code(t_shell *shell, int code)
{
	if (shell)
		shell->last_exit_code = code;
}

int	get_signal_code(t_shell *shell)
{
	if (!shell)
		return (1);
	return (shell->last_exit_code);
}
