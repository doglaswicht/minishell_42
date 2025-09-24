/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: procha-r <procha-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:01:03 by procha-r          #+#    #+#             */
/*   Updated: 2025/08/27 14:06:53 by procha-r         ###   ########.fr       */
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

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

typedef enum e_prompt_state
{
	PROMPT_DEFAULT,
	PROMPT_HEREDOC
}	t_prompt_state;

typedef struct s_prompt_info
{
	t_prompt_state	mode;
	int				last_status;
	int				interactive;
}	t_prompt_info;

typedef struct s_shell
{
	t_env			*env;
	int				last_exit_code;
	int				is_running;
	pid_t			last_pid;
	int				**pipes;
	int				pipe_count;
	t_prompt_info	prompt;
}	t_shell;

int		main(int argc, char **argv, char **envp);
int		shell_loop(t_shell *shell);
void	free_shell(t_shell *shell);
void	exit_clean(t_shell *shell, int code);
void	deep_cleanup_on_error(t_shell *shell);

#endif
