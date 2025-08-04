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
#include <readline/readline.h>
#include <readline/history.h>

static void process_line(char *line, t_shell *shell)
{
    t_token *tokens;
    t_cmd   *cmds;

    tokens = tokenize_input(line);
    cmds = parse_tokens_to_cmds(tokens);
    if (cmds)
        execute_pipeline(cmds, shell);
    free_command_list(cmds);
    free_token_list(tokens);
    free(line);
}

int shell_loop(t_shell *shell)
{
    char *line;
    
    shell->is_running = 1;
    while (shell->is_running)
    {
        line = read_user_input();
        if (!line)
            break ;
        if (*line)
            add_history(line);
    
        process_line(line, shell);
    }
    return(0);
}