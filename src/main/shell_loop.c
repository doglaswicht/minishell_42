/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:54:56 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/05 16:54:58 by dleite-b         ###   ########.fr       */
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
    free_user_input(line);
}

int shell_loop(t_shell *shell)
{
    char    *line;

    init_prompt();
    shell->is_running = 1;
    while (shell->is_running && is_interactive_shell())
    {
        line = read_user_input();
        if (!line)
            break ;
        if (*line)
            add_history(line);
        process_line(line, shell);
        set_last_status(shell->last_exit_code);
    }
    return (0);
}