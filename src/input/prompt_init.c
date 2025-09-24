/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:21:36 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 14:22:06 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include <unistd.h>

void	init_prompt(t_shell *shell)
{
	shell->prompt.mode = PROMPT_DEFAULT;
	shell->prompt.last_status = 0;
	shell->prompt.interactive = isatty(STDIN_FILENO);
}
