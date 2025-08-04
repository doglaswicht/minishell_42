/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:51:29 by pedroribeir       #+#    #+#             */
/*   Updated: 2025/06/06 11:54:35 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include "tokenizer.h"
#include <readline/readline.h>
#include <readline/history.h>

int    shell_loop(t_shell *shell)
{
    char	*line;

    shell->is_running = 1;
    while (shell->is_running)
    {
        line = read_user_input();
        if (!line)
            break ;
        if (line)
            add_history(line);
        // Aqui entra o tokenizer e processamento dos comandos futuramente
        free(line);
    }
    return (0);
}