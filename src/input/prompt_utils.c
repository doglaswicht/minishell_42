/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:22:40 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 14:23:00 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_prompt_state	get_prompt_state(t_shell *shell)
{
	return (shell->prompt.mode);
}

void	set_prompt_state(t_shell *shell, t_prompt_state state)
{
	shell->prompt.mode = state;
}

void	set_last_status(t_shell *shell, int status)
{
	shell->prompt.last_status = status;
}

int	get_last_status(t_shell *shell)
{
	return (shell->prompt.last_status);
}

int	is_interactive_shell(t_shell *shell)
{
	return (shell->prompt.interactive);
}
