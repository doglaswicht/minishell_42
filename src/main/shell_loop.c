/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleite-b <dleite-b@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:54:56 by dleite-b          #+#    #+#             */
/*   Updated: 2025/08/06 17:22:38 by dleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "quotes.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;
	char	*expanded;

	expanded = expand_variables(line, shell->env, shell->last_exit_code);
        free_user_input(line);
        if (!expanded)
                return ;
        if (contains_unclosed_quotes(expanded))
        {
                print_error("Error: unclosed quotes");
                shell->last_exit_code = 2;
                free_user_input(expanded);
                return ;
        }
        tokens = tokenize_input(expanded);
	cmds = parse_tokens_to_cmds(tokens);
	if (cmds)
		execute_pipeline(cmds, shell);
	free_command_list(cmds);
	free_token_list(tokens);
	free_user_input(expanded);
}

int	shell_loop(t_shell *shell)
{
	char	*line;

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