/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:54:41 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:54:42 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "input.h"

void	init_readline(void)
{
    if (!is_interactive_shell())
        return ;
    rl_catch_signals = 0;
    set_prompt_state(PROMPT_DEFAULT);
}