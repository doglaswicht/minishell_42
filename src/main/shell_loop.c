/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:51:11 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 15:26:00 by procha-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include "expansion.h"
#include "quotes.h"
#include "signals.h"
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

	init_prompt(shell);
	shell->is_running = 1;
	while (shell->is_running)
	{
		line = read_user_input(shell);
		if (!line)
			break ;
		if (*line && is_interactive_shell(shell))
			add_history(line);
		process_line(line, shell);
		if (g_signal != 0)
		{
			shell->last_exit_code = g_signal;
			g_signal = 0;
		}
		set_last_status(shell, shell->last_exit_code);
	}
	return (0);
}
