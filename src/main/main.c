/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:05:33 by procha-r          #+#    #+#             */
/*   Updated: 2025/06/06 11:48:28 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	shell.env = init_env_from_environ(envp);
	shell.last_exit_code = 0;
	shell.is_running = 1;
	while (shell.is_running)
	{
		line = read_user_input();
		if (!line)
			break ;
		tokens = tokenize_input(line);
		cmds = parse_tokens_to_cmds(tokens);
		if (cmds)
			execute_pipeline(cmds, &shell);
		free_command_list(cmds);
		free_token_list(tokens);
		free(line);
	}
	exit_clean(&shell, 0);
}