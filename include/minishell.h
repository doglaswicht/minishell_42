/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:01:03 by procha-r          #+#    #+#             */
/*   Updated: 2025/06/06 11:48:17 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "tokenizer.h"
# include "parser.h"
# include "redir.h"
# include "exec.h"
# include "builtin.h"
# include "env.h"
# include "cleanup.h"
# include "utils.h"
# include "input.h"

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	int		last_exit_code;
	int		is_running;
}	t_shell;

int		main(int argc, char **argv, char **envp);
int		shell_loop(t_shell *shell);
void	free_shell(t_shell *shell);
void	exit_clean(t_shell *shell, int code);
void	deep_cleanup_on_error(t_shell *shell);

#endif
